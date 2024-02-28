//
// Created by Toksichniy_Ded on 22.02.2024.
//

#ifndef SERVER_REGISTRATION_MESSAGE_H
#define SERVER_REGISTRATION_MESSAGE_H

#include "IMessage.h"
#include "../../../../Business_Logic/Database/Tables/User.h"
#include "../../../../Business_Logic/Database/Tables/Password.h"

class Registration_Message: public IMessage {
protected:
    std::string m_data;
    User* m_user;
    Password* m_password;

public:
    explicit Registration_Message(std::string& data, User* user = nullptr, Password* password = nullptr):
    m_data(std::move(data)), m_user(user), m_password(password){};
    ~Registration_Message() override;
    void Prepare_Data() override;
    Password* Get_Password();
    User* Get_User();
    std::string& Get_Data();
};


#endif //SERVER_REGISTRATION_MESSAGE_H
