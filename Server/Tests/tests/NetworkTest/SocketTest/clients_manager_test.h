
#ifndef SERVER_CLIENT_MANAGER_TEST_H
#define SERVER_CLIENT_MANAGER_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include "../../../Modules/Network/Socket/Client_Manager.h"
#include "../../../Modules/Tools/Containers/Container_Vector.h"
#include "../../../../Modules/Business_Logic/Task/include/Task.h"
#include "../../ThreadTest/thread_test.h"

class Task_Container_Mock : public Task_Container {
public:
    MOCK_METHOD(void, Emplace_Task, (Task * ), (override));
    MOCK_METHOD(int, Size, (), (override));
    MOCK_METHOD(void, Notify_One, (), (override));
    MOCK_METHOD(void, Notify_All, (), (override));
    MOCK_METHOD(bool, Empty, (), (override));
    MOCK_METHOD(Task*, Front_Task, (), (override));
    MOCK_METHOD(void, Condition, (std::function<bool()>), (override));
};

class Client_Socket_Mock : public Client_Socket {
public:
    explicit Client_Socket_Mock(SOCKET socket) : Client_Socket(socket) {};

    MOCK_METHOD(SOCKET, Get_Socket, (), (const, override));
    MOCK_METHOD(void, Send_Message, (std::string & ), (override));
    MOCK_METHOD((std::pair<Client_Socket *, std::vector<char>>), Listen_Socket, (), (override));
    MOCK_METHOD(Client_Socket_Manager*, Get_Client_Socket_Manager, (), (override));
    MOCK_METHOD(void, Delete_Object, (), (override));
};

class Client_Socket_Manager_Mock : public Client_Socket_Manager {
public:
    Client_Socket_Manager_Mock(SOCKET *sk) : Client_Socket_Manager(sk) {};
    MOCK_METHOD(bool, Check_Socket, (), (override));
    MOCK_METHOD(void, Close_Socket, (), (override));
};


class Task_Factory_Mock : public Task_Factory {
public:
    MOCK_METHOD(void, Register_Task, (const std::string&, Task_Creator), (override));
    MOCK_METHOD(Task*, CreateTask, (const std::string&, Client_Socket*, std::string&), (override));
};


class Clients_Manager_Test : public ::testing::Test {

};

#endif