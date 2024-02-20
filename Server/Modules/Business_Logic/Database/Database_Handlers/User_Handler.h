//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_USER_HANDLER_H
#define SERVER_USER_HANDLER_H

#include "../DataMappers/UserMapper.h"
#include "../Pool/Database_Connector.h"

class User_Handler {
protected:
    Database_Connector* m_connector;
    UserMapper* m_mapper;

public:
    bool Create_User(User& new_user);
    User Read_User_By_Telephone_Number(int telephone_number);
    User Read_User_By_UserName(int username);
    bool Update_UserName(User& user);
    bool Delete_User(User& user);
};


#endif //SERVER_USER_HANDLER_H
