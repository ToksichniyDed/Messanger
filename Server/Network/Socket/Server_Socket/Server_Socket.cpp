//
// Created by super on 13.11.2023.
//
#include "Server_Socket.h"

void Server_Socket::Open_Socket() {
    try {
        auto temp = socket(AF_INET, SOCK_STREAM, 0);
        if (temp == INVALID_SOCKET)
            throw std::runtime_error("Invalid server socket!");

        std::cout<<"Create server socket!"<<std::endl;
        m_server_socket = temp;

        Bind_Socket();
        Listening_Socket();
    }
    catch (std::exception &Error) {
        std::cout << "Open_Socket() Error: " << Error.what() << std::endl;
    }
}

void Server_Socket::Close_Socket() {
    closesocket(m_server_socket);
    m_server_socket = INVALID_SOCKET;
}

void Server_Socket::Set_Security_Options() {

}

void Server_Socket::Bind_Socket() {
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(HTONS);
    server_address.sin_addr.s_addr = inet_addr(IP_ADRESS);

    if (bind(m_server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == SOCKET_ERROR) {
        Close_Socket();
        throw std::runtime_error("Error binding socket to address!");
    }
}

void Server_Socket::Accept() {
    while (true) {
        SOCKET temp_client_socket;
        sockaddr_in client_address{};
        int client_address_length = sizeof(client_address);
        temp_client_socket = accept(m_server_socket, (struct sockaddr *) &client_address, &client_address_length);
        Client_Socket *client_socket = new Client_Socket(temp_client_socket);
        std::cout<<"New client accept!"<<std::endl;
        m_client_manager.Add_New_Client(client_socket);
    }
}

void Server_Socket::Listening_Socket() {
    try {
        if (listen(m_server_socket, BACKLOG) == SOCKET_ERROR)
            throw std::runtime_error("Error listening socket to address!");
        std::cout << "Start server! Listening..." << std::endl;
    }
    catch (std::exception &Error) {
        std::cout << "Check_Socket() Error: " << Error.what() << std::endl;
    }
}



