//
// Created by super on 15.11.2023.
//

#include "Client_Manager.h"

//Добавление нового клиента из метода Accept() в классе Server_Socket()
void Client_Manager::Add_New_Client(std::shared_ptr<Client_Socket> clientSocket) {
    m_connected_clients->Emplace_Back(std::move(clientSocket));
}

//Удаление клиента
void Client_Manager::Remove_Client(int temp) {
    std::cout << "Client with socket: " << *m_connected_clients->At(temp)->Get_Socket() << " disconneted!" << std::endl;
    m_connected_clients->Erase(temp);
}

//Метод запускается в отдельном потоке.У него 2 задачи.
//Он иттерируется по вектору подключенных клиентов, для начала проверяя их с помощью метода Check_Socket(),
//существует ли еще подключение. Если нет, то сокет корректно закрывается, указатель удаляется,
// и корректируется вектор подключенных клиентов. Если сокет актуален, то вызывается метод Listen_Socket(),
//который возвращает пару клиентский_сокет*-строку. Если строка не пустая, то парсится с помощью Json_Tools
// для создания задачи соответственно типу сообщения.
void Client_Manager::Listen_Clients() {
    m_should_exit = false;
    while (!m_should_exit) {
        Iteration();
    }
}

void Client_Manager::Stop_Listening() {
    m_should_exit = true;
}

void Client_Manager::Iteration() {
    if (!m_connected_clients->Empty()) {
        for (int i = 0; i < m_connected_clients->Size(); i++) {
            auto client_socket = m_connected_clients->At(i);
            if (!client_socket->Get_Client_Socket_Manager()->Check_Socket()) {
                Remove_Client(i);
                client_socket->Get_Client_Socket_Manager()->Close_Socket();
                continue;
            }

            auto data = client_socket->Listen_Socket();

            if (!data.second.empty()) {
                std::string data_type = Unpack_Json("type", data.second.data());
                std::string parse_data = Unpack_Json("data", data.second.data());

                auto message = m_message_factory->Create_Message(data_type,std::move(parse_data));

                if(!message) {
                    std::cout << "Unknown message type!" << std::endl;
                    Server_Error_Protocol error_message;
                    data.first->Send_Message(error_message.Set_Parametrs().Build_Message());
                    continue;
                }
                auto task = m_task_factory->Create_Task(data_type, std::make_shared<Client_Socket>(*data.first), std::move(message));

                if (!task) {
                    std::cout << "Unknown task type!" << std::endl;
                    Server_Error_Protocol error_message;
                    data.first->Send_Message(error_message.Set_Parametrs().Build_Message());
                    continue;
                }

                m_clients_tasks->Emplace_Task(std::move(task));
                m_clients_tasks->Notify_All();
            }
        }
    }
}

Client_Manager::Client_Manager(std::unique_ptr<Container_Vector<std::shared_ptr<Client_Socket>>> connected_clients,
                               std::shared_ptr<Task_Container> clients_tasks,
                               std::unique_ptr<Task_Factory> task_factory,
                               std::unique_ptr<Message_Factory> messageFactory){

    if(connected_clients)
        m_connected_clients = std::move(connected_clients);

    if(clients_tasks)
        m_clients_tasks = std::move(clients_tasks);

    if(task_factory)
        m_task_factory = std::move(task_factory);

    if(messageFactory)
        m_message_factory = std::move(messageFactory);

    if(!(m_connected_clients && m_clients_tasks && m_task_factory && m_message_factory))
        throw std::runtime_error("Failed create Client_Manager!");
}






