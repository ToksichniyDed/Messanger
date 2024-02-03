
#ifndef SERVER_CLIENT_MANAGER_TEST_H
#define SERVER_CLIENT_MANAGER_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../../Network/Socket/Client_Manager.h"
#include "../../../Tools/Containers/Container_Vector.h"
#include "../../../Business_Logic/Task/Task.h"
#include "../../ThreadTest/thread_test.h"

class Task_Container_Mock : public Task_Container {
public:
    MOCK_METHOD(void, Emplace_Task, (Task * ), ());
    MOCK_METHOD(int, Size, (), ());
    MOCK_METHOD(void, Notify_One, (), ());
    MOCK_METHOD(void, Notify_All, (), ());
    MOCK_METHOD(bool, Empty, (), ());
    MOCK_METHOD(Task*, Front_Task, (), ());
    MOCK_METHOD(void, Condition, (std::function<bool()>), ());
};


class Task_Factory_Mock : public Task_Factory {
public:
    MOCK_METHOD(void, Register_Task, (const std::string&, Task_Creator));
    MOCK_METHOD(Task*, CreateTask, (const std::string&, Client_Socket*, std::string&), ());
};


class Clients_Manager_Test : public ::testing::Test {

};

#endif