add_executable(ThreadTest thread_test.cpp)
target_link_libraries(ThreadTest Thread gmock gmock_main gtest gtest_main pthread)