cmake_minimum_required(VERSION 3.26)
project(Modules)

set(CMAKE_CXX_STANDARD 17)
add_library(Modules INTERFACE)

add_subdirectory(Model)
add_subdirectory(Tools)
add_subdirectory(View)
add_subdirectory(View_Model)

target_link_libraries(Modules INTERFACE Model Tools View View_Model ws2_32)
#target_include_directories(Modules PRIVATE)