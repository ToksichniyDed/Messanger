//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_USER_HANDLER_H
#define SERVER_USER_HANDLER_H

#include "../../DataMappers/UserMapper.h"
#include "../../DataMappers/PasswordMapper.h"
#include "../../Pool/Database_Connector.h"

class User_Handler {
protected:
    std::shared_ptr<IDatabase_Connector> m_connector = nullptr;
    std::unique_ptr<UserMapper> m_mapper = nullptr;

public:
    explicit User_Handler() = default;
    explicit User_Handler(std::shared_ptr<IDatabase_Connector> connector, std::unique_ptr<UserMapper> mapper);
    void Set_Connector(std::shared_ptr<IDatabase_Connector> connector);
    void Disconnect_Connector();
    bool Create_User(User& new_user, int passwordid, pqxx::work& transaction);
    User Read_User_By_Telephone_Number(User& user);
    User Read_User_By_UserName(User& user);
    bool Update_UserName(User& user);
    bool Delete_User(User& user);
};


#endif //SERVER_USER_HANDLER_H
