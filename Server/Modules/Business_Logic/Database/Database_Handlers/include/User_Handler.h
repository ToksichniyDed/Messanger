//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_USER_HANDLER_H
#define SERVER_USER_HANDLER_H

#include "../../DataMappers/UserMapper.h"
#include "../../Pool/Database_Connector.h"

class User_Handler {
protected:
    Database_Connector* m_connector;
    UserMapper* m_mapper;

public:
    explicit User_Handler(Database_Connector* connector = nullptr, UserMapper* mapper = nullptr);
    void Set_Connector(Database_Connector* connector);
    void Disconnect_Connector();
    bool Create_User(User& new_user);
    User Read_User_By_Telephone_Number(User& user);
    User Read_User_By_UserName(User& user);
    bool Update_UserName(User& user);
    bool Delete_User(User& user);
};


#endif //SERVER_USER_HANDLER_H
