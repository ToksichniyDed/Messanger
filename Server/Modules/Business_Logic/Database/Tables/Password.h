//
// Created by Toksichniy_Ded on 14.02.2024.
//

#ifndef SERVER_PASSWORD_H
#define SERVER_PASSWORD_H

#include <string>

class Password {
protected:
    int m_password_id;
    std::string m_hash;
    std::string m_salt;

public:
    void Set_PasswordID(int password_id);
    [[nodiscard]] int Get_PasswordID()const;

    void Set_Hash(std::string hash);
    [[nodiscard]] std::string Get_Hash() const;

    void Set_Salt(std::string salt);
    [[nodiscard]] std::string Get_Salt() const;
};


#endif //SERVER_PASSWORD_H
