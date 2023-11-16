//
// Created by super on 23.11.2023.
//

#ifndef SERVER_CLIENT_SOCKET_MANAGER_H
#define SERVER_CLIENT_SOCKET_MANAGER_H

#include "Client_Socket.h"

class Client_Socket_Manager{
public:
    std::pair<Client_Socket *, std::vector<char>> Listen_Socket(Client_Socket* m_socket);
    void Send_Message(Client_Socket* m_socket, std::string& message);
};


#endif //SERVER_CLIENT_SOCKET_MANAGER_H
