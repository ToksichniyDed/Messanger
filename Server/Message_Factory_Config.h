//
// Created by Toksichniy_Ded on 28.02.2024.
//

#ifndef SERVER_MESSAGE_FACTORY_CONFIG_H
#define SERVER_MESSAGE_FACTORY_CONFIG_H

#include "Modules/Network/Socket/Message/include/Message_Factory.h"
#include "Modules/Network/Socket/Message/include/Authorizatiion_Message_Creator.h"
#include "Modules/Network/Socket/Message/include/Registration_Message_Creator.h"

std::unique_ptr<Message_Factory> Message_Factory_Config(){

    auto message_factory = std::make_unique<Message_Factory>(std::make_unique<std::unordered_map<std::string, std::unique_ptr<IMessage_Creator>>>()) ;

    message_factory->Register_Message("authorization_message", std::make_unique<Authorization_Message_Creator>());
    message_factory->Register_Message("registration_message",std::make_unique<Registration_Message_Creator>());

    return std::move(message_factory);
}

#endif //SERVER_MESSAGE_FACTORY_CONFIG_H
