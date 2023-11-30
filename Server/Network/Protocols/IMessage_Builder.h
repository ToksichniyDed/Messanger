//
// Created by super on 23.11.2023.
//

#ifndef SERVER_IMESSAGE_BUILDER_H
#define SERVER_IMESSAGE_BUILDER_H

#include "../../Tools/Json_Tools.h"

//Интерфейс билдера сообщений

class IMessage_Builder {
public:
    virtual std::string Build_Message() = 0;
    virtual  IMessage_Builder& Set_Parametrs() = 0;
    virtual  IMessage_Builder& Set_Content(std::string& data) = 0;
    virtual void Validate_Message() = 0;
    virtual void Clear_Message() = 0;
};


#endif //SERVER_IMESSAGE_BUILDER_H
