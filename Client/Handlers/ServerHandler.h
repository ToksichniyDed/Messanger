//
// Created by super on 09.09.2023.
//

#ifndef CLIENT_SERVERHANDLER_H
#define CLIENT_SERVERHANDLER_H

#include <winsock2.h>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <iostream>
#include <map>
#include <condition_variable>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "User_ServerHandler_Mediator.h"

class ServerHandler {
private:
    //мьютексы и условные переменные
    std::mutex m_access_to_message_to_server_queue;
    std::mutex m_access_to_message_from_server_queue;

    //Переменные
    SOCKET m_server_socket;
    User_ServerHandler_Mediator* m_mediator = nullptr;

    static ServerHandler* m_instance;
    explicit ServerHandler(SOCKET client_socket);


public:
    static ServerHandler* GetInstance(SOCKET client_socket);
    ~ServerHandler(){delete m_instance;}

    //Общение с User
    void Set_Mediator(User_ServerHandler_Mediator* mediator);

    //Общение с сервером
    void Read_from_Server();
    void Write_to_Server();

};


#endif //CLIENT_SERVERHANDLER_H
