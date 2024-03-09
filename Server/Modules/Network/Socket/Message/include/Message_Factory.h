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
#include "IMessage_Creator.h"

class Message_Factory{
public:
    using Message_Map = std::unordered_map<std::string, std::unique_ptr<IMessage_Creator>>;

protected:
    Message_Map m_message_map;

public:
    virtual ~Message_Factory() = default;
    virtual void Register_Message(std::string type_message, std::unique_ptr<IMessage_Creator> creator);
    virtual std::unique_ptr<IMessage> Create_Message(std::string& data_type, std::string data);
};

void Message_Factory::Register_Message(/*std::move()*/std::string type_message, std::unique_ptr<IMessage_Creator> creator) {
    auto it = m_message_map.find(type_message);
    if(it == m_message_map.end())
        m_message_map.insert(std::make_pair(std::move(type_message), std::move(creator)));
    else
        it->second = std::move(creator);
}

std::unique_ptr<IMessage> Message_Factory::Create_Message(std::string& data_type, std::string data) {
    auto it = m_message_map.find(data_type);
    if(it != m_message_map.end()){
        return it->second->Create_Message(data);
    }
    return nullptr;
}

#endif //SERVER_MESSAGE_FACTORY_H
