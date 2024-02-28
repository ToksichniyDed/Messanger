//
// Created by Toksichniy_Ded on 28.02.2024.
//

#ifndef SERVER_AUTHORIZATIION_MESSAGE_CREATOR_H
#define SERVER_AUTHORIZATIION_MESSAGE_CREATOR_H

#include "Authorization_Message.h"
#include "IMessage_Creator.h"

class Authorization_Message_Creator: public IMessage_Creator {
public:
    IMessage* Create_Message(std::string& data) override{
        return dynamic_cast<IMessage*>(new Authorization_Message(data));
    }
};

#endif //SERVER_AUTHORIZATIION_MESSAGE_CREATOR_H
