//
// Created by super on 06.09.2023.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(int count_of_pools) {
    for(int i = 0;i<count_of_pools;i++){
        m_thread_pools.emplace_back([this](){
            std::cout<<"Thread "<<std::this_thread::get_id() <<" was created!"<<std::endl;
            while(true){

                {
                    std::cout<<"Thread " <<std::this_thread::get_id() << " wait client!"<<std::endl;
                    std::unique_lock<std::mutex> lock(m_access_to_client_queue);
                    m_conditional_variable.wait(lock,[this]{return !m_client_queue.empty();});
                    std::cout<<"Thread " <<std::this_thread::get_id() << " start handle client connection!"<<std::endl;
                }

                ClientHandler* client_handle = new ClientHandler(m_client_queue.front());
                m_client_queue.pop();

                while(client_handle->Check_Connection_With_Client())
                {
                    client_handle->Read_Client_Data();
                }
                std::cout<<"Thread "<<std::this_thread::get_id() <<" is free!"<<std::endl;
            }
        });
    }
}



void ThreadPool::Push_New_Client(SOCKET client_socket){
    std::lock_guard<std::mutex> lock(m_access_to_client_queue);
    m_client_queue.emplace(client_socket);
    m_conditional_variable.notify_one();
}

ThreadPool::~ThreadPool(){
    for (std::thread &thread: m_thread_pools) {
        std::cout << "Thread " << std::this_thread::get_id() << " is close!" << std::endl;
        thread.join();
    }
}