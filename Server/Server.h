//
// Created by super on 11.09.2023.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <iostream>
#include <winsock2.h>
#include <memory>

#include "ThreadPool.h"
#include "ClientHandler/ClientHandler.h"


class Server {
private:
    static Server* m_server_instance;
    SOCKET m_server_socket;
    sockaddr_in m_server_address;
    std::unique_ptr<ThreadPool> m_thread_pool;
    Server();

public:

    static Server* GetInstance();
    void Start();
    void Turn_Off() const;
    void Listening();
};


#endif //SERVER_SERVER_H
