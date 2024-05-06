//
// Created by super on 23.11.2023.
//

#ifndef SERVER_CLIENT_SOCKET_H
#define SERVER_CLIENT_SOCKET_H

#include <memory>
#ifdef __unix__
#include <fcntl.h>
#endif

#include "Client_Socket_Manager.h"

//Реализация клиентского сокета.

class Client_Socket{
protected:
    std::shared_ptr<MySocketType> m_socket;
    std::shared_ptr<Client_Socket_Manager> m_socket_manager;

public:
    explicit Client_Socket(std::shared_ptr<Client_Socket_Manager> manager, std::shared_ptr<MySocketType> socket);
    virtual std::pair<std::shared_ptr<Client_Socket>, std::vector<char>> Listen_Socket();
    virtual void Send_Message( std::string message);
    virtual std::shared_ptr<Client_Socket_Manager> Get_Client_Socket_Manager();
    [[nodiscard]] virtual std::shared_ptr<MySocketType> Get_Socket() const;
};

#endif //SERVER_CLIENT_SOCKET_H
