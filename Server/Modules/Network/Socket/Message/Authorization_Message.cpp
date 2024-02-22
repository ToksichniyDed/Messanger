//
// Created by Toksichniy_Ded on 22.02.2024.
//

#include "Authorization_Message.h"

//Потом переписать, m_data тоже надо будет распаковать на password_data и user_data
void Authorization_Message::Prepare_Data() {
    m_password = new Password;
    m_password->Set_Hash(Unpack_Json("hash", m_data));
    m_password->Set_Salt(Unpack_Json("salt", m_data));

    m_user = new User;
    m_user->Set_UserName(Unpack_Json("username",m_data));
    m_user->Set_Telephone_Number(Unpack_Json("telephone_number",m_data));
    m_user->Set_UserID(m_password->Get_UserID());
}

User* Authorization_Message::Get_User() {
    return m_user;
}

Password* Authorization_Message::Get_Password() {
    return m_password;
}