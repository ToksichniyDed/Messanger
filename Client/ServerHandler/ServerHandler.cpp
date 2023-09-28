//
// Created by super on 09.09.2023.
//

#include "ServerHandler.h"

ServerHandler *ServerHandler::m_instance;
std::queue<std::string> ServerHandler::m_message_to_server_queue;

ServerHandler::ServerHandler(SOCKET client_socket) : m_server_socket(client_socket) {}

void ServerHandler::Read_from_Server() {
    std::vector<char> server_buffer(1024);
    while(true){
        int received_bytes = recv(m_server_socket,server_buffer.data(),1024,0);
        if (received_bytes <= 0)
            throw std::runtime_error("Failed read server message!");
        {
            std::unique_lock<std::mutex> lock(m_access_to_message_from_server_queue);
            m_message_from_server_queue.emplace(server_buffer);
        }

        while(!m_message_from_server_queue.empty()){
            {
                Handle_Server_Message();
            }
        }

    }
}



void ServerHandler::Write_to_Server(std::string type, const std::string &message) {
    try {
        boost::property_tree::ptree client_pt;
        client_pt.put("type", type);
        client_pt.put("data", message);

        std::stringstream ss;
        boost::property_tree::write_json(ss, client_pt);
        std::string message_to_server = ss.str();

        {
            std::unique_lock<std::mutex> lock(m_access_to_message_to_server_queue);
            m_message_to_server_queue.emplace(message_to_server);
        }
        while (!m_message_to_server_queue.empty()) {
            int sent_bytes = send(m_server_socket, m_message_to_server_queue.front().c_str(), m_message_to_server_queue.front().size(), 0);
            {std::unique_lock<std::mutex> lock(m_access_to_message_to_server_queue);
            m_message_to_server_queue.pop();}
            if (sent_bytes < 0) {
                throw std::runtime_error("Failed to send message!");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return;
    }

}

ServerHandler *ServerHandler::GetInstance(SOCKET client_socket) {
    if (m_instance == nullptr)
        m_instance = new ServerHandler(client_socket);

    return m_instance;
}

UserInterface *ServerHandler::Get_User_Interface() {
    return m_interface;
}

void ServerHandler::Handle_Server_Message() {
    std::string message_from_server;
    {
        std::unique_lock<std::mutex> lock(m_access_to_message_from_server_queue);
        message_from_server = m_message_from_server_queue.front().data();
        m_message_from_server_queue.pop();
    }
    boost::property_tree::ptree server_pt;
    std::istringstream iss(message_from_server);
    boost::property_tree::read_json(iss, server_pt);

    auto message_type = server_pt.get<std::string>("type");

    if(message_type == "registration_data_ans")
    {

    }
}

