//
// Created by Toksichniy_Ded on 22.02.2024.
//

#include "Authorization_Message.h"

//Потом переписать, m_data тоже надо будет распаковать на password_data и user_data
void Authorization_Message::Prepare_Data() {
    m_password = std::make_shared<Password>();
    m_password->Set_Hash(Unpack_Json("hash", m_data));
    m_password->Set_Salt(Unpack_Json("salt", m_data));

    m_user = std::make_shared<User>();
    m_user->Set_UserName(Unpack_Json("username",m_data));
    m_user->Set_Telephone_Number(Unpack_Json("telephone_number",m_data));
    m_user->Set_Password_Id(m_password->Get_PasswordID());
}

std::shared_ptr<User> Authorization_Message::Get_User() {
    return m_user;
}

std::shared_ptr<Password> Authorization_Message::Get_Password() {
    return m_password;
}

std::string &Authorization_Message::Get_Data() {
    return m_data;
}

Authorization_Message::Authorization_Message(std::string &data, std::shared_ptr<User> user,
                                             std::shared_ptr<Password> password) {
    m_data = std::move(data);

    if(user)
        m_user = std::move(user);

    if(password)
        m_password = std::move(password);

    if(!(m_user && m_password))
        throw std::runtime_error("Failed create Authorization_Message!");
}

