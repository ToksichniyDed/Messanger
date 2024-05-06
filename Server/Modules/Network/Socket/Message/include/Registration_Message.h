//
// Created by Toksichniy_Ded on 22.02.2024.
//

#ifndef SERVER_REGISTRATION_MESSAGE_H
#define SERVER_REGISTRATION_MESSAGE_H

#include <memory>
#include <utility>

#include "IMessage.h"
#include "../../../../Business_Logic/Database/Tables/User.h"
#include "../../../../Business_Logic/Database/Tables/Password.h"
#include "../../../../Tools/Json_Tools.h"

class Registration_Message: public IMessage {
protected:
    std::string m_data;
    std::shared_ptr<User> m_user = nullptr;
    std::shared_ptr<Password> m_password = nullptr;

public:
    explicit Registration_Message(std::string& data):m_data(std::move(data)){}
    explicit Registration_Message(std::string& data, std::shared_ptr<User> user, std::shared_ptr<Password> password);
    void Prepare_Data() override;
    std::shared_ptr<Password> Get_Password();
    std::shared_ptr<User> Get_User();
    std::string& Get_Data();
};


#endif //SERVER_REGISTRATION_MESSAGE_H
