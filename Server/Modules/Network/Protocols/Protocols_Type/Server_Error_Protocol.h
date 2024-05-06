//
// Created by Toksichniy_Ded on 09.03.2024.
//

#ifndef SERVER_SERVER_ERROR_PROTOCOL_H
#define SERVER_SERVER_ERROR_PROTOCOL_H

#include "../IMessage_Builder.h"

//Правила сбора сообщения-ответа для уведомлении об ошибки на сервере

class Server_Error_Protocol: public IMessage_Builder {
private:
    std::string m_parametrs;
    std::string m_data;
public:

    std::string Build_Message() override;
    IMessage_Builder& Set_Parametrs() override;
    IMessage_Builder& Set_Content(std::string data) override;
    void Clear_Message() override;
};


#endif //SERVER_SERVER_ERROR_PROTOCOL_H
