//
// Created by super on 23.11.2023.
//

#ifndef SERVER_CLIENT_SOCKET_H
#define SERVER_CLIENT_SOCKET_H

#include "Client_Socket_Manager.h"

class Client_Socket{
public:
    SOCKET m_socket = 0;
    Client_Socket_Manager* m_socket_manager = nullptr;

public:
    explicit Client_Socket(SOCKET socket);
    ~Client_Socket();
    std::pair<Client_Socket *, std::vector<char>> Listen_Socket();
    void Send_Message( std::string& message);
    Client_Socket_Manager* Get_Client_Socket_Manager();
};


#endif //SERVER_CLIENT_SOCKET_H
