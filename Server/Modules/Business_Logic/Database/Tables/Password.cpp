//
// Created by Toksichniy_Ded on 14.02.2024.
//

#include "Password.h"

#include <utility>

void Password::Set_PasswordID(int password_id) {
 m_password_id = password_id;
}

int Password::Get_PasswordID() const {
    return m_password_id;
}

void Password::Set_Hash(std::string hash) {
m_hash = std::move(hash);
}

std::string Password::Get_Hash() const {
    return m_hash;
}

void Password::Set_Salt(std::string salt) {
m_salt = std::move(salt);
}

std::string Password::Get_Salt() const {
    return m_salt;
}
