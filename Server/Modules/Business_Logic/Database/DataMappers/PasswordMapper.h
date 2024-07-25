//
// Created by Toksichniy_Ded on 14.02.2024.
//

#ifndef SERVER_PASSWORDMAPPER_H
#define SERVER_PASSWORDMAPPER_H

#include "../Tables/Password.h"
#include <pqxx/pqxx>


class PasswordMapper {
public:
    Password Mapping(pqxx::result& query_result){
        Password password;

        if(!query_result.empty()){
            password.Set_PasswordID(query_result[0][0].as<int>());
            password.Set_Hash(query_result[0][2].as<std::string>());
            password.Set_Salt(query_result[0][3].as<std::string>());
        }

        return std::move(password);
    };
};


#endif //SERVER_PASSWORDMAPPER_H
