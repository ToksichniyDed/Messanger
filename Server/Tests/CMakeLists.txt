add_subdirectory(googletest-1.14.0)
add_library(Tests INTERFACE)
add_subdirectory(tests/NetworkTest)
target_link_libraries(Tests INTERFACE NetworkTest)