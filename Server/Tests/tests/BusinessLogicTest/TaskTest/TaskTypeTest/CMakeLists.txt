add_library(TaskTypeTest authorization_task_test.cpp
registration_task_test.cpp)

add_executable(TaskTypeTest_EX authorization_task_test.cpp
        registration_task_test.cpp)

target_link_libraries(TaskTypeTest Business_Logic Tools Database Network gmock gmock_main gtest gtest_main pthread)
target_link_libraries(TaskTypeTest_EX Business_Logic Tools Database Network gmock gmock_main gtest gtest_main pthread)