//
// Created by Toksichniy_Ded on 07.02.2024.
//

#ifndef SERVER_AUTHORIZATION_TASK_TEST_H
#define SERVER_AUTHORIZATION_TASK_TEST_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../../Business_Logic/Database/Database_Manager.h"
#include "../../tests/NetworkTest/SocketTest/clients_manager_test.h"

class Database_Manager_Mock : public Database_Manager{
public:
    Database_Manager_Mock(): Database_Manager(nullptr){};
    MOCK_METHOD(bool, Insert, (std::string& , (std::vector<std::map<std::string, std::string>> &)), (override));
    MOCK_METHOD(bool, Update, (std::string &, (std::vector<std::map<std::string, std::string>> &),
            std::string &), (override));
    MOCK_METHOD(bool, Delete, (std::string &, std::string &), (override));
    MOCK_METHOD((std::vector<std::map<std::string, std::string>>), ExecuteCustomSelect,
                (std::string &, const std::string &,
            const std::string &), (override));
};



class AuthorizationTaskTest : public ::testing::Test{

};


#endif //SERVER_AUTHORIZATION_TASK_TEST_H
