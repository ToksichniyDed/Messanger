//
// Created by Toksichniy_Ded on 22.02.2024.
//

#ifndef SERVER_AUTHORIZATION_MESSAGE_H
#define SERVER_AUTHORIZATION_MESSAGE_H

#include <memory>
#include <utility>

#include "IMessage.h"
#include "../../../../Business_Logic/Database/Tables/User.h"
#include "../../../../Business_Logic/Database/Tables/Password.h"

class Authorization_Message: public IMessage{
protected:
    std::string m_data;
    std::shared_ptr<User> m_user;
    std::shared_ptr<Password> m_password;

public:
    explicit Authorization_Message(std::string& data, std::shared_ptr<User> user = nullptr, std::shared_ptr<Password> password = nullptr):
    m_data(std::move(data)), m_user(std::move(user)), m_password(std::move(password)){};
    void Prepare_Data() override;
    std::string& Get_Data();
    std::shared_ptr<User> Get_User();
    std::shared_ptr<Password> Get_Password();
};


#endif //SERVER_AUTHORIZATION_MESSAGE_H
