//
// Created by super on 08.09.2023.
//

#include "ClientHandler.h"

ClientHandler::ClientHandler(SOCKET client_socket):m_client_socket(client_socket) {
}

void ClientHandler::Read_Client_Data() {
    char client_buffer[2048];

    try {
        int received_bytes = recv(m_client_socket, client_buffer, 2048, 0);
        if (received_bytes <= 0)
            throw std::runtime_error("Failed read client message!");
        else {
            std::string received_json(client_buffer, received_bytes);

            boost::property_tree::ptree client_pt;
            std::istringstream iss(received_json);
            boost::property_tree::read_json(iss, client_pt);

            std::string message_type = client_pt.get<std::string>("type");

            if (message_type == "message") {
                std::string message_data = client_pt.get<std::string>("data");
                std::cout << "Client message: " << message_data << std::endl;
            } else {
                std::cout << "No handle for this type of message!" << std::endl;
            }
        }
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return;
    }

}

void ClientHandler::Send_Data_To_Client() {

}

bool ClientHandler::Check_Connection_With_Client() const {
    if(send(m_client_socket,"check",1,0) == SOCKET_ERROR)
        return false;
    return true;
}

void ClientHandler::Start_Handle() {

}
