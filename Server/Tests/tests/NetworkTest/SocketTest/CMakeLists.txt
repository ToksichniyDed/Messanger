add_executable(SocketTest client_socket_test.cpp
        server_socket_test.cpp
)

target_link_libraries(SocketTest Socket gmock gmock_main gtest gtest_main pthread)