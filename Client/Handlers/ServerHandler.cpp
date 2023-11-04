//
// Created by super on 09.09.2023.
//

#include "ServerHandler.h"

ServerHandler* ServerHandler::m_instance = nullptr;

ServerHandler::ServerHandler(SOCKET client_socket) : m_server_socket(client_socket) {}

void ServerHandler::Read_from_Server() {
    std::vector<char> server_buffer(1024);
    while (true) {
        try {
            int received_bytes = recv(m_server_socket, server_buffer.data(), server_buffer.size(), 0);
            if (received_bytes <= 0)
                throw std::runtime_error("Failed read server message!");
            std::string str(server_buffer.begin(), server_buffer.end());
            str.resize(received_bytes);
            m_mediator->Set_Data_To_User_From_ServerHandler(str);
        }
        catch (std::exception& Error)
        {
            //std::cout<<"Error: "<< Error.what()<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void ServerHandler::Write_to_Server() {
    while(true) {
        std::unique_lock<std::mutex> lock(m_access_to_message_to_server_queue);
        m_mediator->Get_CV_To_ServerHandler().wait(lock,[&]{return !m_mediator->Message_To_Server_Queue_Is_Empty();});
        std::string message_to_server = m_mediator->Get_Data_To_ServerHandler_From_User();
        try {
            int sent_bytes = send(m_server_socket, message_to_server.c_str(),
                                  static_cast<int>(message_to_server.size()), 0);
            if (sent_bytes < 0) {
                throw std::runtime_error("Failed to send message!");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        catch (std::exception &Error) {
            std::cout << "Error: " << Error.what() << std::endl;
        }
    }
}

ServerHandler *ServerHandler::GetInstance(SOCKET client_socket) {
    if (m_instance == nullptr)
        m_instance = new ServerHandler(client_socket);
    return m_instance;
}

void ServerHandler::Set_Mediator(User_ServerHandler_Mediator *mediator) {
    m_mediator = mediator;
}



