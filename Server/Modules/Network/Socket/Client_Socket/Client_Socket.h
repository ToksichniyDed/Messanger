//
// Created by super on 23.11.2023.
//

#ifndef SERVER_CLIENT_SOCKET_H
#define SERVER_CLIENT_SOCKET_H

#include <memory>

#include "Client_Socket_Manager.h"

//Реализация клиентского сокета.

class Client_Socket{
public:
    SOCKET m_socket = 0;
    std::shared_ptr<Client_Socket_Manager> m_socket_manager;

public:
    explicit Client_Socket(std::shared_ptr<Client_Socket_Manager> manager = nullptr, SOCKET socket = 0);
    virtual std::pair<Client_Socket *, std::vector<char>> Listen_Socket();
    virtual void Send_Message( std::string message);
    virtual std::shared_ptr<Client_Socket_Manager> Get_Client_Socket_Manager();
    virtual SOCKET Get_Socket() const;
    virtual void Delete_Object();
};

#endif //SERVER_CLIENT_SOCKET_H
