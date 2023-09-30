//
// Created by super on 10.09.2023.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <iostream>
#include <winsock2.h>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "Handlers/ServerHandler.h"
#include "User/User.h"

class Client {
private:
    //Клиент и обработчик
    static Client* m_instance;

    sockaddr_in m_server_address{};
    SOCKET m_server_socket{};
    Client();

    //Оброботчик соединения с сервером, с действиями клиента
    ServerHandler* m_server_handler;
    User* m_user;

public:
    static Client* GetInstance();
    ~Client(){delete m_server_handler; delete m_user; std::cout<<"Delete client!"<<std::endl;}
    void Connect();
    void Disconnect() const;
    bool Is_Connected() const;
    bool Start_Communication();
    ServerHandler* Get_ServerHandler();
};


#endif //CLIENT_CLIENT_H
