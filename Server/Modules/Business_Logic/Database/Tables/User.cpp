//
// Created by Toksichniy_Ded on 14.02.2024.
//

#include "User.h"

#include <utility>

void User::Set_UserID(int userid) {
    m_user_id = userid;
}

int User::Get_UserID() const {
    return m_user_id;
}

void User::Set_UserName(std::string username) {
    m_username = std::move(username);
}

std::string User::Get_UserName() const {
    return m_username;
}

void User::Set_Telephone_Number(std::string telephone_number) {
    m_telephone_number = std::move(telephone_number);
}

std::string User::Get_Telephone_Number() const {
    return m_telephone_number;
}
