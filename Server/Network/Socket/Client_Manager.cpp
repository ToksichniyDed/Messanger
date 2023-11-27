//
// Created by super on 15.11.2023.
//

#include "Client_Socket/Client_Socket_Manager.h"
#include "Client_Manager.h"

void Client_Manager::Add_New_Client(Client_Socket *clientSocket) {
    m_connected_clients.Emplace_Back(clientSocket);
}

void Client_Manager::Remove_Client(int temp) {
    m_connected_clients.Erase(temp);
}

void Client_Manager::Listen_Clients() {
    while (true) {
        for (int i = 0; i < m_connected_clients.Size(); i++) {
            auto client_socket = m_connected_clients.At(i);
            if (!client_socket->Get_Client_Socket_Manager()->Check_Socket()) {
                m_connected_clients.Erase(i);
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
                    m_clients_tasks.Emplace_Task(task);
                }
                else
                    std::cout<<"Unknown task type!"<<std::endl;
                m_clients_tasks.Notify_All();
            }
        }
    }
}



