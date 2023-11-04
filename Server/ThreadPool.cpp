//
// Created by super on 06.09.2023.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(int count_of_pools) {
    m_thread_pools.emplace_back([this](){
        std::cout<<"Thread "<<std::this_thread::get_id() <<" was created!"<<std::endl;
        Listening_Connected_Clients();
    });

    for(int i = 1;i<count_of_pools;i++){
        m_thread_pools.emplace_back([this](){
            std::cout<<"Thread "<<std::this_thread::get_id() <<" was created!"<<std::endl;
            Handlers_Threads();
        });
    }
}



void ThreadPool::Push_New_Client(SOCKET client_socket){
    std::lock_guard<std::mutex> lock(m_access_to_client_queue);
    std::cout<<"Client was connected!"<<std::endl;
    m_client_queue.push_back(client_socket);
}

ThreadPool::~ThreadPool(){
    for (std::thread &thread: m_thread_pools) {
        std::cout << "Thread " << std::this_thread::get_id() << " is close!" << std::endl;
        thread.join();
    }
}

void ThreadPool::Listening_Connected_Clients() {
    while(true) {
        if(m_client_queue.empty())
            continue;

        fd_set read_file_descriptors;//это структура данных, представляющая набор соксетов.
        // Она используется для указания, какие соксеты будут мониториться функцией select.
        FD_ZERO(&read_file_descriptors);//эта функция инициализирует набор соксетов read_file_descriptors, делая его пустым (без ни одного соксета).

        //Проверка, что клиенты из очереди до  сих пор подключены
        for (auto it = m_client_queue.begin(); it != m_client_queue.end();) {
            const SOCKET &client_socket = *it;

            boost::property_tree::ptree check_pt;
            check_pt.put("type", "check");
            check_pt.put("data", "1");

            std::stringstream ss;
            boost::property_tree::write_json(ss, check_pt);
            std::string check_client = ss.str();

            if (send(client_socket, check_client.c_str(), check_client.size(), 0) == SOCKET_ERROR) {
                std::lock_guard<std::mutex> lock(m_access_to_client_queue);
                closesocket(client_socket);
                it = m_client_queue.erase(it);
            } else {
                FD_SET(client_socket, &read_file_descriptors);
                ++it;
            }
        }

        int max_file_descriptor = *std::max_element(m_client_queue.begin(), m_client_queue.end());

        int activity = select(max_file_descriptor + 1, &read_file_descriptors, nullptr, nullptr, nullptr);

        if (activity == -1)
            perror("select");
        else {
            for (const SOCKET &client_socket: m_client_queue) {
                if (FD_ISSET(client_socket, &read_file_descriptors)) {
                    std::cout<<"Socket "<< client_socket << " have message!"<<std::endl;
                    try {
                        std::vector<char> client_buffer(1024);
                        int received_bytes = recv(client_socket, client_buffer.data(), 1024, 0);
                        if (received_bytes <= 0)
                            throw std::runtime_error("Failed read client message!");
                        {
                            client_buffer.resize(received_bytes);
                            std::cout<<client_buffer.data()<<std::endl;
                            std::lock_guard<std::mutex> lock(m_access_to_clients_tasks);
                            m_received_messages_from_clients.emplace(client_socket,client_buffer);
                            m_conditional_variable.notify_one();
                        }
                    }catch (std::exception &Error) {
                        std::cout << "Error: " << Error.what() << std::endl;
                    }
                }
            }
        }
    }
}

void ThreadPool::Handlers_Threads() {
    while(true){
        std::cout<<"Thread "<<std::this_thread::get_id() <<" wait client task!"<<std::endl;
        {
            std::unique_lock<std::mutex> lock(m_access_to_clients_tasks);
            m_conditional_variable.wait(lock, [this] { return !m_received_messages_from_clients.empty(); });
            std::cout << "Thread " << std::this_thread::get_id() << " start handle client task!" << std::endl;
            ClientHandler handle_client(m_received_messages_from_clients.front().first);
            handle_client.Read_Client_Data(std::move(m_received_messages_from_clients.front().second));
            m_received_messages_from_clients.pop();
        }
        std::cout<<"Thread "<<std::this_thread::get_id() <<" is free!"<<std::endl;
    }

}


