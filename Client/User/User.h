//
// Created by super on 30.09.2023.
//

#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include <iostream>

#include "../Handlers/MessengerHandler.h"
#include "../Handlers/ServerHandler.h"
#include "../Interface/UserInterface.h"


class User {
private:
    UserInterface* m_interface = UserInterface::GetInstance();
    ServerHandler* m_server_handler;
    std::string m_telephone_number;
    std::string m_username;
    MessengerHandler* m_messenger_handler{};

public:
    explicit User(ServerHandler* server_handler);
    ~User(){delete m_interface;
    delete m_messenger_handler;}
    bool User_Registration();
    bool User_Authorization();

};


#endif //CLIENT_USER_H
