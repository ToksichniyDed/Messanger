//
// Created by Toksichniy_Ded on 14.02.2024.
//

#ifndef SERVER_USERMAPPER_H
#define SERVER_USERMAPPER_H

#include "../Tables/User.h"
#include "../Pool/Database_Connector.h"

class UserMapper {
private:
    IDatabase_Connector* m_database_connector;

public:
    UserMapper(IDatabase_Connector* database_connector);
    User Find_By_Id(int user_id);
    void Save (User& user);
    void Update (User& user);
    void Delete (User& user);
};


#endif //SERVER_USERMAPPER_H
