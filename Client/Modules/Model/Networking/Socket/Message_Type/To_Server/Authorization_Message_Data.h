//
// Created by super on 30.11.2023.
//

#ifndef CLIENT_AUTHORIZATION_MESSAGE_DATA_H
#define CLIENT_AUTHORIZATION_MESSAGE_DATA_H

#include <string>
#include "../IMessage.h"

class Authorization_Message_Data: public IMessage{
protected:
    std::string m_telephone_number;
    std::string m_password;

public:
    Authorization_Message_Data(std::string tel_number, std::string pass):m_telephone_number(std::move(tel_number)), m_password(std::move(pass)){}
    [[nodiscard]] std::string Get_Telephone_Number()const{
        return m_telephone_number;
    }
    [[nodiscard]] std::string Get_Password()const{
        return m_password;
    }
    void Prepare_Data(){}
};


#endif //CLIENT_AUTHORIZATION_MESSAGE_DATA_H
