//
// Created by Toksichniy_Ded on 14.02.2024.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <string>


class User {
protected:
    int m_user_id = 0;
    int m_password_id = 0;
    std::string m_username;
    std::string m_telephone_number;

public:
    void Set_UserID(int userid);
    [[nodiscard]] int Get_UserID() const;

    void Set_UserName(std::string username);
    [[nodiscard]] std::string Get_UserName() const;

    void Set_Telephone_Number(std::string telephone_number);
    [[nodiscard]] std::string Get_Telephone_Number() const;

    void Set_Password_Id(int passwordid);
    [[nodiscard]] int Get_Password_Id() const;

    //Перегрузка для сравнения с пустыми объектам User. Например, при возврате пустого объект при поиске в БД
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
};


#endif //SERVER_USER_H
