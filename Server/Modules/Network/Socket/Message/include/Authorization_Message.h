//
// Created by Toksichniy_Ded on 22.02.2024.
//

#ifndef SERVER_AUTHORIZATION_MESSAGE_H
#define SERVER_AUTHORIZATION_MESSAGE_H

#include "IMessage.h"
#include "../../../../Business_Logic/Database/Tables/User.h"
#include "../../../../Business_Logic/Database/Tables/Password.h"

class Authorization_Message: public IMessage{
protected:
    std::string m_data;
    User* m_user;
    Password* m_password;

public:
    explicit Authorization_Message(std::string& data, User* user = nullptr, Password* password = nullptr):
    m_data(std::move(data)), m_user(user), m_password(password){};
    ~Authorization_Message() override;
    void Prepare_Data() override;
    std::string& Get_Data();
    User* Get_User();
    Password* Get_Password();
};


#endif //SERVER_AUTHORIZATION_MESSAGE_H
