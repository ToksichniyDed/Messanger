//
// Created by Toksichniy_Ded on 07.02.2024.
//

#include "authorization_task_test.h"

TEST_F(AuthorizationTaskTest,EmptyQueryTest){
    Database_Manager_Mock databaseManagerMock;
    Client_Socket_Mock clientSocketMock(123);
    std::string data = "data";
    std::vector<std::map<std::string ,std::string >> vec;

    Authorization_Task authorizationTask(&clientSocketMock, data, &databaseManagerMock);

    EXPECT_CALL(databaseManagerMock, ExecuteCustomSelect).WillOnce(::testing::Return(vec));
    EXPECT_CALL(clientSocketMock, Send_Message).Times(0);

    authorizationTask.Execute();

}

TEST_F(AuthorizationTaskTest, NotEmptyQueryTest_CheckPasswordFail){
    Database_Manager_Mock databaseManagerMock;
    Client_Socket_Mock clientSocketMock(123);
    std::string data = "data";
    std::string select_part = "user_id, password, salt";
    std::string where_part = "telephone_number = 'telephone_number'";
    std::string user = "User";
    std::vector<std::map<std::string ,std::string >> vec, vec2;
    std::map<std::string, std::string> map{
            {"salt", "salt"},
            {"salt", "salt"}
    };
    vec.emplace_back(map);

    Authorization_Task authorizationTask(&clientSocketMock, data, &databaseManagerMock);

    EXPECT_CALL(databaseManagerMock, ExecuteCustomSelect(user,select_part,where_part)).WillOnce(::testing::Return(vec));
    select_part = "user_id, username";
    where_part = "telephone_number = 'telephone_number' AND password = 'check_password'";
    EXPECT_CALL(databaseManagerMock, ExecuteCustomSelect(user,select_part, where_part )).WillOnce(::testing::Return(vec2));
    std::string message = "{\n    \"type\": \"authorization_data_ans\",\n    \"data\": \"false\"\n}\n";
    EXPECT_CALL(clientSocketMock, Send_Message(message)).Times(1);

    authorizationTask.Execute();
}

TEST_F(AuthorizationTaskTest, NotEmptyQueryTest_CheckPasswordSuccess){
Database_Manager_Mock databaseManagerMock;
Client_Socket_Mock clientSocketMock(123);
std::string data = "data";
std::string select_part = "user_id, password, salt";
std::string where_part = "telephone_number = 'telephone_number'";
std::string user = "User";
std::vector<std::map<std::string ,std::string >> vec, vec2;
std::map<std::string, std::string> map{
        {"salt", "salt"},
};
vec.emplace_back(map);

Authorization_Task authorizationTask(&clientSocketMock, data, &databaseManagerMock);

EXPECT_CALL(databaseManagerMock, ExecuteCustomSelect(user,select_part,where_part)).WillOnce(::testing::Return(vec));
select_part = "user_id, username";
where_part = "telephone_number = 'telephone_number' AND password = 'check_password'";
EXPECT_CALL(databaseManagerMock, ExecuteCustomSelect(user,select_part, where_part )).WillOnce(::testing::Return(vec));
std::string message = "{\n    \"type\": \"authorization_data_ans\",\n    \"data\": \"true\"\n}\n";
EXPECT_CALL(clientSocketMock, Send_Message(message)).Times(1);

authorizationTask.Execute();
}