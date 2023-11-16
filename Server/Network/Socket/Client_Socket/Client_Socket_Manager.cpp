//
// Created by super on 23.11.2023.
//

#include "Client_Socket_Manager.h"

std::pair<Client_Socket *, std::vector<char>> Client_Socket_Manager::Listen_Socket(Client_Socket* m_socket) {
    std::cout << "Socket " << m_socket << " have message!" << std::endl;
    try {
        std::vector<char> client_buffer(1024);
        int received_bytes = recv(m_socket->Get_Socket(), client_buffer.data(), 1024, 0);
        if (received_bytes <= 0)
            throw std::runtime_error("Failed read client message!");
        std::pair<Client_Socket *, std::vector<char>> ans = std::make_pair(m_socket, client_buffer);
        return ans;
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return std::make_pair(m_socket, std::vector<char>());
    }
}

void Client_Socket_Manager::Send_Message(Client_Socket* m_socket, std::string &message) {
    try {
        if(!send(m_socket->Get_Socket(), message.c_str(), message.size(), 0))
            throw std::runtime_error("Failed send message!");
    }
    catch (std::exception& Error)
    {
        std::cout<<"Error: "<<Error.what()<<std::endl;
    }
}



