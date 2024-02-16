//
// Created by Toksichniy_Ded on 14.02.2024.
//

#include "UserMapper.h"


User UserMapper::Find_By_Id(int user_id) {
    pqxx::connection *connector= m_database_connector->Connector();
    pqxx::work transaction(*connector);

    pqxx::result query_result = transaction.exec("SELECT * FROM User WHERE UserID = " + std::to_string(user_id));

    User user;
    if(!query_result.empty()){
        user.Set_UserID(query_result[0][0].as<int>());
        user.Set_UserName(query_result[0][1].as<std::string>());
        user.Set_Telephone_Number(query_result[0][2].as<std::string>());
    }

    return user;
}

void UserMapper::Save(User &user) {

}

void UserMapper::Update(User &user) {

}

void UserMapper::Delete(User &user) {

}

UserMapper::UserMapper(IDatabase_Connector *database_connector):m_database_connector(database_connector) {

}
