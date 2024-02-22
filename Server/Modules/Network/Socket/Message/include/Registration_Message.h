//
// Created by Toksichniy_Ded on 22.02.2024.
//

#ifndef SERVER_REGISTRATION_PROTOCOL_H
#define SERVER_REGISTRATION_MESSAGE_H

#include "IMessage.h"
#include "Message_Factory.h"
#include "../../../../Business_Logic/Database/Tables/User.h"


class Registration_Message: protected IMessage {
protected:
    User* m_user;

public:
    explicit Registration_Message(std::string data, User* user = nullptr):
    IMessage(data), m_user(user){};
    void Prepare_Data() override;
    User* Get_User();
};


#endif //SERVER_REGISTRATION_PROTOCOL_H
