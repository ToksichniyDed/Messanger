//
// Created by super on 08.09.2023.
//

#include "ClientHandler.h"

[[maybe_unused]] ClientHandler::ClientHandler(SOCKET client_socket) : m_client_socket(client_socket) {
    std::cout << "Create ClientHandler of " << client_socket << " socket!" << std::endl;
}

void ClientHandler::Read_Client_Data(std::vector<char> client_buffer) const {
    try {
        std::string client_str (client_buffer.begin(),client_buffer.end());
        auto message_type = Unpack_Json("type", client_str);

        if (message_type == "message") {
            auto message_data = Unpack_Json("data",client_str);
            std::cout << "Client message: " << message_data << std::endl;
        } else if (message_type == "registration_data") {
            std::cout << "Телефон: " << Unpack_Json("telephone_number", Unpack_Json("data",client_str))
                      << " Номер: " << Unpack_Json("password", Unpack_Json("data",client_str)) << std::endl;

            Send_Data_To_Client("registration_data_ans","true");
        } else if(message_type == "authorization_data"){
            std::cout << "Телефон: " << Unpack_Json("telephone_number", Unpack_Json("data",client_str))
                      << " Номер: " << Unpack_Json("password", Unpack_Json("data",client_str)) << std::endl;

            Send_Data_To_Client("authorization_data_ans","false");
        }
        else {
            std::cout << "No handle for this type of message!" << std::endl;
        }
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return;
    }
}

void ClientHandler::Send_Data_To_Client(const std::string &type, const std::string &message) const {
    try {
        std::string message_to_client = Pack_Json(type, message);

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


