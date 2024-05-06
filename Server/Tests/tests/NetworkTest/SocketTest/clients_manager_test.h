
#ifndef SERVER_CLIENT_MANAGER_TEST_H
#define SERVER_CLIENT_MANAGER_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/di.hpp>

#include "../../../../Modules/Network/Socket/Client_Manager.h"
#include "../../../../Modules/Tools/Containers/Container_Vector.h"
#include "../../../../Modules/Business_Logic/Task/include/Task.h"
#include "../../ThreadTest/thread_test.h"

class Task_Container_Mock : public Task_Container {
public:
    MOCK_METHOD(void, Emplace_Task, (std::unique_ptr<Task> ), (override));
    MOCK_METHOD(int, Size, (), (override));
    MOCK_METHOD(void, Notify_One, (), (override));
    MOCK_METHOD(void, Notify_All, (), (override));
    MOCK_METHOD(bool, Empty, (), (override));
    MOCK_METHOD(std::unique_ptr<Task>, Front_Task, (), (override));
    MOCK_METHOD(void, Condition, (std::function<bool()>), (override));
};

class Client_Socket_Mock : public Client_Socket {
public:
    explicit Client_Socket_Mock(std::shared_ptr<Client_Socket_Manager> manager, std::shared_ptr<MySocketType> socket)
    : Client_Socket(manager, socket) {};

    MOCK_METHOD(std::shared_ptr<MySocketType>, Get_Socket, (), (const, override));
    MOCK_METHOD(void, Send_Message, (std::string  ), (override));
    MOCK_METHOD((std::pair<std::shared_ptr<Client_Socket>, std::vector<char>>), Listen_Socket, (), (override));
    MOCK_METHOD(std::shared_ptr<Client_Socket_Manager>, Get_Client_Socket_Manager, (), (override));
};

class Client_Socket_Manager_Mock : public Client_Socket_Manager {
public:
    explicit Client_Socket_Manager_Mock(std::shared_ptr<MySocketType> sk) : Client_Socket_Manager(sk) {};
    MOCK_METHOD(bool, Check_Socket, (), (override));
    MOCK_METHOD(void, Close_Socket, (), (override));
};

class Pool_Connection_Mock : public Pool_Connection{
public:
    explicit Pool_Connection_Mock(): Pool_Connection(0){}
};


class Task_Factory_Mock : public Task_Factory {
public:
    explicit Task_Factory_Mock(): Task_Factory(std::make_unique<Pool_Connection_Mock>()){}
    MOCK_METHOD(void, Register_Task, (const std::string&, std::unique_ptr<ITask_Creator>), (override));
    MOCK_METHOD(std::unique_ptr<Task>, Create_Task, (const std::string &, std::shared_ptr<Client_Socket> , std::unique_ptr<IMessage> ), (override));
};

class Message_Factory_Mock : public Message_Factory{
public:
    explicit Message_Factory_Mock():Message_Factory(std::make_unique<std::unordered_map<std::string, std::unique_ptr<IMessage_Creator>>>()){}
    MOCK_METHOD(std::unique_ptr<IMessage>, Create_Message, (std::string& , std::string), (override));
};


class Clients_Manager_Test : public ::testing::Test {

};

#endif