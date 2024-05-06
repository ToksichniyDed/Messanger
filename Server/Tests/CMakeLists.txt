project(Tests)

add_subdirectory(googletest-1.14.0)
add_subdirectory(tests/NetworkTest)
add_subdirectory(tests/ThreadTest)
add_subdirectory(tests/BusinessLogicTest)

add_executable(Tests tests/all_test.cpp)

target_link_libraries(Tests PUBLIC ThreadTest NetworkTest BusinessLogicTest gtest gtest_main gmock gmock_main)