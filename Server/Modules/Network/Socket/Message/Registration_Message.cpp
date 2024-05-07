//
// Created by Toksichniy_Ded on 22.02.2024.
//

#include "Registration_Message.h"

void Registration_Message::Prepare_Data() {
    m_user = std::make_shared<User>();
    auto username = Unpack_Json("username", m_data);
    auto telephone_number = Unpack_Json("telephone_number", m_data);
    if (!(username == "Key not found" || username == "Error during JSON deserialization"))
        m_user->Set_UserName(username);
    if (!(telephone_number == "Key not found" || telephone_number == "Error during JSON deserialization"))
        m_user->Set_Telephone_Number(telephone_number);

    m_password = std::make_shared<Password>();

    auto password = Unpack_Json("password", m_data);
    if (!(password == "Key not found" || password == "Error during JSON deserialization"))
        m_password->Set_Password(password);
}

std::shared_ptr<User> Registration_Message::Get_User() {
    return m_user;
}

std::string &Registration_Message::Get_Data() {
    return m_data;
}

std::shared_ptr<Password> Registration_Message::Get_Password() {
    return m_password;
}

Registration_Message::Registration_Message(std::string &data, std::shared_ptr<User> user,
                                           std::shared_ptr<Password> password) {
    m_data = std::move(data);

    if (user)
        m_user = std::move(user);

    if (password)
        m_password = std::move(password);

    if (!(m_user && m_password))
        throw std::runtime_error("Failed create Registration_Message!");
}


