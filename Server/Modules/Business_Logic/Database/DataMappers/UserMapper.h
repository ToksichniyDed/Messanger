//
// Created by Toksichniy_Ded on 14.02.2024.
//

#ifndef SERVER_USERMAPPER_H
#define SERVER_USERMAPPER_H

#include "../Tables/User.h"
#include <pqxx/pqxx>

class UserMapper {
public:
    User Mapping(pqxx::result& query_result){
        User user;

        if(!query_result.empty()){
            user.Set_UserID(query_result[0][0].as<int>());
            user.Set_UserName(query_result[0][1].as<std::string>());
            user.Set_Telephone_Number(query_result[0][2].as<std::string>());
        }

        return std::move(user);
    };
};


#endif //SERVER_USERMAPPER_H
