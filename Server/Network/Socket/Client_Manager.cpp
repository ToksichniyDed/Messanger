//
// Created by super on 15.11.2023.
//

#include "Client_Socket/Client_Socket_Manager.h"
#include "Client_Manager.h"

//Добавление нового клиента из метода Accept() в классе Server_Socket()
void Client_Manager::Add_New_Client(Client_Socket *clientSocket) {
    m_connected_clients.Emplace_Back(clientSocket);
}

//Удаление клиента
void Client_Manager::Remove_Client(int temp) {
    std::cout<<"Client with socket: "<<m_connected_clients.At(temp)->Get_Socket()<<" disconneted!"<<std::endl;
    m_connected_clients.Erase(temp);
}

//Метод запускается в отдельном потоке.У него 2 задачи.
//Он иттерируется по вектору подключенных клиентов, для начала проверяя их с помощью метода Check_Socket(),
//существует ли еще подключение. Если нет, то сокет корректно закрывается, указатель удаляется,
// и корректируется вектор подключенных клиентов. Если сокет актуален, то вызывается метод Listen_Socket(),
//который возвращает пару клиентский_сокет*-строку. Если строка не пустая, то парсится с помощью Json_Tools
// для создания задачи соответственно типу сообщения.
void Client_Manager::Listen_Clients() {
    while (true) {
        if(!m_connected_clients.Empty())
        for (int i = 0; i < m_connected_clients.Size(); i++) {
            auto client_socket = m_connected_clients.At(i);
            if (!client_socket->Get_Client_Socket_Manager()->Check_Socket()) {
                Remove_Client(i);
                client_socket->Get_Client_Socket_Manager()->Close_Socket();
                delete client_socket;
                continue;
            }

            auto data = client_socket->Listen_Socket();

            if (!data.second.empty()) {
                std::string data_type = Unpack_Json("type", data.second.data());
                std::string parse_data = Unpack_Json("data", data.second.data());

                auto task = task_factory.CreateTask(data_type,data.first,parse_data);

                if(task) {
                    m_clients_tasks .Emplace_Task(std::move(task));
                }
                else
                    std::cout<<"Unknown task type!"<<std::endl;

                m_clients_tasks.Notify_All();
            }
        }
    }
}



