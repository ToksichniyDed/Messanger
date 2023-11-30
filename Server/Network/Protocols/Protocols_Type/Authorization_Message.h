//
// Created by super on 23.11.2023.
//

#ifndef SERVER_AUTHORIZATION_MESSAGE_H
#define SERVER_AUTHORIZATION_MESSAGE_H

#include "../IMessage_Builder.h"

//Правила сбора сообщения-ответа для задачи авторизации

class Authorization_Message: public IMessage_Builder {
private:
    std::string m_parametrs;
    std::string m_data;
public:
    std::string Build_Message() override;
    IMessage_Builder& Set_Parametrs() override;
    IMessage_Builder& Set_Content(std::string& data) override;
    void Validate_Message() override;
    void Clear_Message() override;
};


#endif //SERVER_AUTHORIZATION_MESSAGE_H
