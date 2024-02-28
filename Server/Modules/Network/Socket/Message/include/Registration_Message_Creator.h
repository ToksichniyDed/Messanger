//
// Created by Toksichniy_Ded on 28.02.2024.
//

#ifndef SERVER_REGISTRATION_MESSAGE_CREATOR_H
#define SERVER_REGISTRATION_MESSAGE_CREATOR_H

#include "Registration_Message.h"
#include "IMessage_Creator.h"

class Registration_Message_Creator: public IMessage_Creator {
public:
    IMessage* Create_Message(std::string& data) override{
        return dynamic_cast<IMessage*>(new Registration_Message(data));
    }
};

#endif //SERVER_REGISTRATION_MESSAGE_CREATOR_H
