//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_IMESSAGE_H
#define SERVER_IMESSAGE_H

#include <string>

#include "../../../../Tools/Json_Tools.h"

class IMessage {
protected:
    std::string m_type;
    std::string m_data;

public:
    explicit IMessage(std::string& data):
    m_type(Unpack_Json("message_type", data)),m_data(Unpack_Json("data", data)) {};
    IMessage() = default;
    virtual ~IMessage() = default;
    virtual void Prepare_Data() = 0;
    virtual std::string Get_Data(){return m_data;};
    virtual std::string Get_Type(){return m_type;};
};

#endif //SERVER_IMESSAGE_H
