//
// Created by super on 09.09.2023.
//

#include "ServerHandler.h"

ServerHandler *ServerHandler::m_instance;
std::queue<std::string> ServerHandler::m_message_queue;

ServerHandler::ServerHandler(SOCKET client_socket) : m_client_socket(client_socket) {}

void ServerHandler::Read_from_Server() {

}

void ServerHandler::Write_to_Server(std::string type, const std::string &message) const {

    try {
        boost::property_tree::ptree client_pt;
        client_pt.put("type", type);
        client_pt.put("data", message);

        std::stringstream ss;
        boost::property_tree::write_json(ss, client_pt);
        std::string message_to_server = ss.str();

        m_message_queue.emplace(message_to_server);

        while (!m_message_queue.empty()) {
            int sent_bytes = send(m_client_socket, m_message_queue.front().c_str(), m_message_queue.front().size(), 0);
            m_message_queue.pop();
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

