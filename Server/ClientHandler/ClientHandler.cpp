//
// Created by super on 08.09.2023.
//

#include "ClientHandler.h"

[[maybe_unused]] ClientHandler::ClientHandler(SOCKET client_socket) : m_client_socket(client_socket) {
    std::cout << "Create ClientHandler of " << client_socket << " socket!" << std::endl;
}

void ClientHandler::Read_Client_Data(std::vector<char> client_buffer) {
    try {
        std::string received_json(client_buffer.data(), client_buffer.size());

        boost::property_tree::ptree client_pt;
        std::istringstream iss(received_json);
        boost::property_tree::read_json(iss, client_pt);

        auto message_type = client_pt.get<std::string>("type");

        if (message_type == "message") {
            auto message_data = client_pt.get<std::string>("data");
            std::cout << "Client message: " << message_data << std::endl;
        } else if (message_type == "registration_data") {
            auto registration_data = client_pt.get<std::string>("data");
            boost::property_tree::ptree registration_data_pt;
            std::istringstream r_iss(registration_data);
            boost::property_tree::read_json(r_iss, registration_data_pt);
            std::cout << "Телефон: " << registration_data_pt.get<std::string>("telephone_number")
                      << " Номер: " << registration_data_pt.get<std::string>("password") << std::endl;
            Send_Data_To_Client("registration_data_ans","true");
        } else {
            std::cout << "No handle for this type of message!" << std::endl;
        }
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return;
    }
}

void ClientHandler::Send_Data_To_Client(std::string type, const std::string &message) {
    try {
        boost::property_tree::ptree server_pt;
        server_pt.put("type", type);
        server_pt.put("data", message);

        std::stringstream ss;
        boost::property_tree::write_json(ss, server_pt);
        std::string message_to_client = ss.str();

        int sent_bytes = send(m_client_socket, message_to_client.c_str(),message_to_client.size(),0);
        if (sent_bytes < 0) {
            throw std::runtime_error("Failed to send message!");
        }
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return;
    }
}


