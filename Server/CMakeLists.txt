cmake_minimum_required(VERSION 3.26)
project(Server)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
find_package(PostgreSQL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PostgreSQL_INCLUDE_DIRS})

add_executable(Server main.cpp
        ThreadPool.cpp
        ThreadPool.h
        ClientHandler/ClientHandler.cpp
        ClientHandler/ClientHandler.h
        Server.cpp
        Server.h
        Tools/Json_Tools.cpp
        Tools/Json_Tools.h
)

target_link_libraries(Server PRIVATE ws2_32.lib ${Boost_LIBRARIES} ${PostgreSQL_LIBRARIES})
