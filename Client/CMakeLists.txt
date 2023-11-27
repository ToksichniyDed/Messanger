cmake_minimum_required(VERSION 3.26)
project(Client)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Client main.cpp
        Handlers/ServerHandler.cpp
        Handlers/ServerHandler.h
        Interface/UserInterface.h
        Interface/UserInterface.cpp
        Client.cpp
        Client.h
        Handlers/MessengerHandler.cpp
        Handlers/MessengerHandler.h
        User/User.cpp
        User/User.h
        Tools/Json_Tools.cpp
        Tools/Json_Tools.h
)

target_link_libraries(Client PRIVATE ws2_32.lib ${Boost_LIBRARIES})
