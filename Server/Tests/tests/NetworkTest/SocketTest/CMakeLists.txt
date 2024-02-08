add_library(SocketTest
        clients_manager_test.cpp
)

target_link_libraries(SocketTest Socket Business_Logic gmock gmock_main gtest gtest_main pthread)