//
// Created by Toksichniy_Ded on 14.02.2024.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <string>


class User {
protected:
    int m_user_id;
    std::string m_username;
    std::string m_telephone_number;

public:
    void Set_UserID(int userid);
    int Get_UserID() const;

    void Set_UserName(std::string username);
    std::string Get_UserName() const;

    void Set_Telephone_Number(std::string telephone_number);
    std::string Get_Telephone_Number() const;
};


#endif //SERVER_USER_H
