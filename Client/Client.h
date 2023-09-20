//
// Created by super on 10.09.2023.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <iostream>
#include <winsock2.h>

#include "ServerHandler/ServerHandler.h"

class Client {
private:
    static Client* m_instance;
    ServerHandler* m_server_handler;
    sockaddr_in m_server_address{};
    SOCKET m_client_socket{};
    Client();

public:
    static Client* GetInstance();
    ~Client(){delete m_server_handler;
        std::cout<<"Delete client!"<<std::endl;}
    void Connect();
    void Disconnect() const;
    bool Is_Connected() const;
    bool Start_Communication();
};


#endif //CLIENT_CLIENT_H
