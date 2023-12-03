add_subdirectory(googletest-1.14.0)

add_library(Tests INTERFACE)

target_link_libraries(Tests INTERFACE gtest gtest_main)