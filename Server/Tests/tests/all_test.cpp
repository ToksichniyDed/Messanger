#include "gtest/gtest.h"

#include "../tests/BusinessLogicTest/TaskTest/TaskTypeTest/authorization_task_test.cpp"
#include "../tests/BusinessLogicTest/TaskTest/TaskTypeTest/registration_task_test.cpp"
#include "../tests/NetworkTest/ProtocolsTest/protocols_test.cpp"
#include "../tests/NetworkTest/SocketTest/clients_manager_test.cpp"
#include "../tests/ThreadTest/thread_test.cpp"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
