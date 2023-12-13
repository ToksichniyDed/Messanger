//
// Created by Toksichniy_Ded on 12.12.2023.
//

#ifndef SERVER_CLIENT_SOCKET_TEST_H
#define SERVER_CLIENT_SOCKET_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket_Manager.h"

class Mock_Client_Socket: public Client_Socket {
private:
    using SocketData = std::pair<Client_Socket*, std::vector<char>>;

public:
    Mock_Client_Socket(): Client_Socket(INVALID_SOCKET) {}
    MOCK_METHOD(SocketData , Listen_Socket, (), (override));
    MOCK_METHOD(void, Send_Message, (std::string&), (override));
    MOCK_METHOD(Client_Socket_Manager*, Get_Client_Socket_Manager, (), (override));
    MOCK_METHOD(SOCKET, Get_Socket, (), (const, override));
};

class Mock_Client_Socket_Test : public ::testing::Test {
protected:
    Mock_Client_Socket mock_socket;

public:
    //Mock_Client_Socket_Test()=default;
};

class Mock_Client_Socket_Manager: public Client_Socket_Manager {
public:
    Mock_Client_Socket_Manager(SOCKET socket): Client_Socket_Manager(&socket){}
    MOCK_METHOD(void , Close_Socket, (), (override));
    MOCK_METHOD(bool , Check_Socket, (), (override));
};

class Mock_Client_Socket_Manager_Test: public ::testing::Test {
protected:
    Mock_Client_Socket_Manager mockClientSocket;
public:
    Mock_Client_Socket_Manager_Test(SOCKET socket = 123): mockClientSocket(socket){};
};

#endif //SERVER_CLIENT_SOCKET_TEST_H
