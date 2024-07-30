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

void Password::Set_Password(std::string pass) {
    m_password = pass;
}

std::string Password::Get_Password() const {
    return m_password;
}

bool Password::operator==(const Password &other) const {
    return m_password_id==other.m_password_id && m_hash == other.m_hash && m_salt==other.m_salt;
}

bool Password::operator!=(const Password &other) const {
    return m_password_id!=other.m_password_id && m_hash != other.m_hash && m_salt!=other.m_salt;
}
