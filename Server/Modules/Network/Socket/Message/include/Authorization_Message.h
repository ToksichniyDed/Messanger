//
// Created by Toksichniy_Ded on 22.02.2024.
//

#ifndef SERVER_AUTHORIZATION_PROTOCOL_H
#define SERVER_AUTHORIZATION_PROTOCOL_H

#include "IMessage.h"
#include "../../../Business_Logic/Database/Tables/User.h"
#include "../../../Business_Logic/Database/Tables/Password.h"

class Authorization_Message: protected IMessage{
protected:
    User* m_user;
    Password* m_password;

public:
    explicit Authorization_Message(std::string data, User* user = nullptr, Password* password = nullptr):
    IMessage(data), m_user(user), m_password(password){};
    void Prepare_Data() override;
    User* Get_User();
    Password* Get_Password();
};


#endif //SERVER_AUTHORIZATION_PROTOCOL_H
