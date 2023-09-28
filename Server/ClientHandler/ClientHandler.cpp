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
        } else {
            std::cout << "No handle for this type of message!" << std::endl;
        }
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return;
    }
}

void ClientHandler::Send_Data_To_Client() {

}


