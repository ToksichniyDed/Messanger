//
// Created by Toksichniy_Ded on 28.02.2024.
//

#ifndef SERVER_MESSAGE_FACTORY_CONFIG_H
#define SERVER_MESSAGE_FACTORY_CONFIG_H

#include "Modules/Network/Socket/Message/include/Message_Creator_Headers.h"
#include "Modules/Network/Socket/Message/include/Message_Factory.h"

void Message_Factory_Config(){
    Message_Factory message_factory;

    message_factory.Register_Message("authorization_message", new Authorization_Message_Creator);
    message_factory.Register_Message("registration_message",new Registration_Message_Creator);
}

#endif //SERVER_MESSAGE_FACTORY_CONFIG_H
