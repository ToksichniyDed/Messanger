//
// Created by Toksichniy_Ded on 13.12.2023.
//

#ifndef SERVER_SERVER_SOCKET_TEST_H
#define SERVER_SERVER_SOCKET_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../../Network/Socket/Server_Socket/Server_Socket.h"

class Mock_Server_Socket: public Server_Socket {
public:
    MOCK_METHOD(void, Bind_Socket, (), (override));
    MOCK_METHOD(void, Listening_Socket, (), (override));
    MOCK_METHOD(void ,Open_Socket ,(), (override));
    MOCK_METHOD(void , Close_Socket,(), (override));
    MOCK_METHOD(void , Accept,(), (override));
    MOCK_METHOD(void ,Listening_Clients_Socket ,(), (override));
};

class Mock_Server_Socket_Test:public testing::Test{
protected:
    Mock_Server_Socket serverSocket;;
};


#endif //SERVER_SERVER_SOCKET_TEST_H
