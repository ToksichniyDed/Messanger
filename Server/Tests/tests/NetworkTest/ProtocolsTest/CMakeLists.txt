add_library(ProtocolsTest protocols_test.cpp)

add_executable(ProtocolsTest_EX protocols_test.cpp)

target_link_libraries(ProtocolsTest Protocols gmock gmock_main gtest gtest_main pthread)
target_link_libraries(ProtocolsTest_EX Protocols gmock gmock_main gtest gtest_main pthread)