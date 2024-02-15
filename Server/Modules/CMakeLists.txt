cmake_minimum_required(VERSION 3.26)
project(Modules)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Business_Logic)
add_subdirectory(Network)
add_subdirectory(Tools)
add_subdirectory(Thread)

add_library(Modules INTERFACE)

target_link_libraries(Modules INTERFACE Tools Network Thread Business_Logic)