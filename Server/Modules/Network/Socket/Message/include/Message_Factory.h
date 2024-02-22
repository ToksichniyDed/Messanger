//
// Created by Toksichniy_Ded on 22.02.2024.
//

#ifndef SERVER_MESSAGE_FACTORY_H
#define SERVER_MESSAGE_FACTORY_H

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

#include "Message_Headers.h"

class Message_Factory{
protected:
    using Message_Creator = std::function<IMessage*(std::string)>;
    std::unordered_map<std::string, Message_Creator> Message_Registry;

public:
    virtual void Registry_Message(std::string type_message, Message_Creator creator);
    virtual IMessage* Create_Message(std::string& data_type, std::string data);
};

void Message_Factory::Registry_Message(/*std::move()*/std::string type_message, Message_Factory::Message_Creator creator) {
    Message_Registry[type_message] = std::move(creator);
}

IMessage* Message_Factory::Create_Message(std::string& data_type, std::string data) {
    auto it = Message_Registry.find(data_type);
    if(it != Message_Registry.end()){
        return it->second(std::move(data));
    }
    return nullptr;
}

#endif //SERVER_MESSAGE_FACTORY_H
