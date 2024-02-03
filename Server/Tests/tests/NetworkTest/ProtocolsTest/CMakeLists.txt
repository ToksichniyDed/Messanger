add_executable(ProtocolsTest protocols_test.cpp)

target_link_libraries(ProtocolsTest Protocols gmock gmock_main gtest gtest_main pthread)