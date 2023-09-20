//
// Created by super on 11.09.2023.
//

#include "Server.h"

Server::Server() =default;
Server* Server::m_server_instance;

void Server::Start() {
    m_server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(m_server_socket == INVALID_SOCKET)
        throw std::runtime_error ("Create socket is failed!");

    m_server_address.sin_family = AF_INET;
    m_server_address.sin_port = htons(8080);
    m_server_address.sin_addr.s_addr = INADDR_ANY;

    if(bind(m_server_socket, (struct sockaddr*)&m_server_address, sizeof(m_server_address)) == SOCKET_ERROR){
        closesocket(m_server_socket);
        throw std::runtime_error ("Error binding socket to address!");
    }

    m_thread_pool = std::make_unique<ThreadPool>(5);
}

void Server::Turn_Off() const {
    closesocket(m_server_socket);
    std::cout<<"The server was closed!"<<std::endl;
}

void Server::Listening() {
    std::cout<<"Start server! Listening..."<<std::endl;
    if(listen(m_server_socket,5) ==  SOCKET_ERROR){
        throw std::runtime_error ("Error listening socket to address!");
    }

    while (true) {
        int client_socket;
        sockaddr_in client_address{};
        int client_address_length = sizeof(client_address);
        client_socket = accept(m_server_socket, (struct sockaddr *) &client_address, &client_address_length);

        m_thread_pool->Push_New_Client(client_socket);
    }
}

Server* Server::GetInstance() {
    if(m_server_instance == nullptr)
        m_server_instance = new Server();
    return m_server_instance;
}


