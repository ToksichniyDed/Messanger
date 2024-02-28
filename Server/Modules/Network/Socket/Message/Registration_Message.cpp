//
// Created by Toksichniy_Ded on 22.02.2024.
//

#include "Registration_Message.h"

void Registration_Message::Prepare_Data() {
    m_user = new User();
    m_user->Set_UserName(Unpack_Json("username", m_data));
    m_user->Set_Telephone_Number(Unpack_Json("telephone_number", m_data));

    m_password = new Password();
    m_password->Set_Password(Unpack_Json("password", m_data));
}

User *Registration_Message::Get_User() {
    return m_user;
}

std::string &Registration_Message::Get_Data() {
    return m_data;
}

Password *Registration_Message::Get_Password() {
    return m_password;
}

Registration_Message::~Registration_Message() {
    delete m_user;
    delete m_password;
}


