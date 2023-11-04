//
// Created by super on 30.09.2023.
//

#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include <iostream>

#include "../Handlers/MessengerHandler.h"
#include "../Interface/UserInterface.h"
#include "../Handlers/User_ServerHandler_Mediator.h"

class User {
private:
    UserInterface* m_interface = UserInterface::GetInstance();
    MessengerHandler* m_messenger_handler{};
    User_ServerHandler_Mediator* m_mediator;

public:
    ~User(){delete m_interface;
    delete m_messenger_handler;}
    bool User_Registration_Authorization(std::string type);
    void Set_Mediator(User_ServerHandler_Mediator* mediator);

};


#endif //CLIENT_USER_H
