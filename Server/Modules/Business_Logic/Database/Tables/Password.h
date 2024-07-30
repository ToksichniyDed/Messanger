//
// Created by Toksichniy_Ded on 14.02.2024.
//

#ifndef SERVER_PASSWORD_H
#define SERVER_PASSWORD_H

#include <string>

class Password {
protected:
    int m_password_id = 0;
    std::string m_hash;
    std::string m_salt;
    std::string m_password;

public:
    void Set_PasswordID(int password_id);
    [[nodiscard]] int Get_PasswordID() const;

    void Set_Hash(std::string hash);
    [[nodiscard]] std::string Get_Hash() const;

    void Set_Salt(std::string salt);
    [[nodiscard]] std::string Get_Salt() const;

    void Set_Password(std::string pass);
    [[nodiscard]] std::string Get_Password()const;

    bool operator==(const Password& other) const;
    bool operator!=(const Password& other) const;
};


#endif //SERVER_PASSWORD_H
