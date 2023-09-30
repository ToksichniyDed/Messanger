//
// Created by super on 09.09.2023.
//

#include "ServerHandler.h"

ServerHandler* ServerHandler::m_instance = nullptr;

ServerHandler::ServerHandler(SOCKET client_socket) : m_server_socket(client_socket) {}

void ServerHandler::Read_from_Server() {
    std::vector<char> server_buffer(1024);
    while (true) {
        int received_bytes = recv(m_server_socket, server_buffer.data(), 1024, 0);
        if (received_bytes <= 0)
            throw std::runtime_error("Failed read server message!");
        {
            std::unique_lock<std::mutex> lock(m_access_to_message_from_server_queue);
            m_message_from_server_queue.emplace(server_buffer);
        }

        while (!m_message_from_server_queue.empty()) {
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
            int sent_bytes = send(m_server_socket, m_message_to_server_queue.front().c_str(),
                                  m_message_to_server_queue.front().size(), 0);
            {
                std::unique_lock<std::mutex> lock(m_access_to_message_to_server_queue);
                m_message_to_server_queue.pop();
            }
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

void ServerHandler::Handle_Server_Message() {
    std::string message_from_server;
    {
        std::unique_lock<std::mutex> lock(m_access_to_message_from_server_queue);
        message_from_server = m_message_from_server_queue.front().data();
        m_message_from_server_queue.pop();
    }

    try {
        if(message_from_server == "check")
            return;
        boost::property_tree::ptree server_pt;
        std::istringstream iss(message_from_server);
        boost::property_tree::read_json(iss, server_pt);

        auto message_type = server_pt.get<std::string>("type");
        auto message_data = server_pt.get<std::string>("data");

        {
            std::lock_guard<std::mutex> lock(m_access_to_handle_message_from_server_queue);
            m_handle_message_from_server_queue.emplace_back(std::move(message_type), std::move(message_data));
        }
        m_conditional_variable.notify_one();
    } catch (const boost::property_tree::json_parser::json_parser_error& e) {
        // Обработка ошибки парсинга JSON
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        std::cout<<message_from_server;
    }
}


std::mutex &ServerHandler::Get_Access_To_Handle_Message_From_Server_Queue_Mutex() {
    return m_access_to_handle_message_from_server_queue;
}

std::condition_variable &ServerHandler::Get_Conditional_Variable() {
    return m_conditional_variable;
}

std::vector<std::pair<std::string,std::string>>& ServerHandler::Get_Handle_Message_From_Server_Queue() {
    return m_handle_message_from_server_queue;
}



