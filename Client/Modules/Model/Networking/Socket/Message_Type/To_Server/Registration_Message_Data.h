//
// Created by super on 30.11.2023.
//

#ifndef CLIENT_REGISTRATION_MESSAGE_DATA_H
#define CLIENT_REGISTRATION_MESSAGE_DATA_H

#include <string>
#include "../IMessage.h"

#include "../../Tools/Json_Tools.h"

class Registration_Message_Data: public IMessage{
protected:
    std::string m_telephone_number;
    std::string m_password;
    std::string m_prepared_data;

public:
    Registration_Message_Data(std::string tel_number, std::string pass): m_telephone_number(std::move(tel_number)), m_password(std::move(pass)){}
    [[nodiscard]] std::string Get_Telephone_Number()const{
        return m_telephone_number;
    }
    [[nodiscard]] std::string Get_Password()const{
        return m_password;
    }
    [[nodiscard]] std::string  Get_Prepared_Data() const override{
        return m_prepared_data;
    }
    void Prepare_Data() override{
        std::string json_number, json_password, json_data;
        json_number = Pack_Json("telephone_number",m_telephone_number);
        json_password = Pack_Json("password",m_password);
        json_data = Pack_Json("data", json_number+json_password);
        m_prepared_data = Pack_Json("registration_message",json_data);
    }
};

#endif //CLIENT_REGISTRATION_MESSAGE_DATA_H
