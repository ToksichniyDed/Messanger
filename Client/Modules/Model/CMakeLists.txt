add_library(Model Thread_Pool.cpp)

add_subdirectory(Networking)

target_link_libraries(Model PUBLIC Networking)