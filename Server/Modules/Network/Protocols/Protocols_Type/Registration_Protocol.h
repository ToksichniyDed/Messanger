//
// Created by super on 23.11.2023.
//

#ifndef SERVER_REGISTRATION_PROTOCOL_H
#define SERVER_REGISTRATION_PROTOCOL_H

#include "../IMessage_Builder.h"

//Правила сбора сообщения-ответа для задачи регистрации

class Registration_Protocol: public IMessage_Builder{
private:
    std::string m_parametrs;
    std::string m_data;

public:
    std::string Build_Message() override;
    IMessage_Builder& Set_Parametrs() override;
    IMessage_Builder& Set_Content(std::string data) override;
    void Clear_Message() override;
};


#endif //SERVER_REGISTRATION_PROTOCOL_H
