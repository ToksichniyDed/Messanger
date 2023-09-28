//
// Created by super on 10.09.2023.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <iostream>
#include <winsock2.h>
#include <locale>
#include <condition_variable>

#include "ServerHandler/ServerHandler.h"

class Client {
private:
    std::condition_variable m_notification_registration_data;
    std::mutex m_registration_ans_mutex;
    static Client* m_instance;
    ServerHandler* m_server_handler{};
    sockaddr_in m_server_address{};
    SOCKET m_server_socket{};
    Client();

public:
    static Client* GetInstance();
    ~Client(){delete m_server_handler;
        std::cout<<"Delete client!"<<std::endl;}
    void Connect();
    void Write_Message();
    void Disconnect() const;
    bool Is_Connected() const;
    bool Start_Communication();
    bool Registration();
    std::string Get_Password();
    std::string Get_Telephone_Number();
};


#endif //CLIENT_CLIENT_H
