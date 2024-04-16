add_library(Socket Client_Manager.cpp
        Client_Socket/Client_Socket_Manager.cpp
        Client_Socket/Client_Socket.cpp
        Server_Socket/Server_Socket.cpp)

add_subdirectory(Message)

if(WIN32)
    target_link_libraries(Socket ws2_32 Tools Thread Business_Logic Message)
else()
    target_link_libraries(Socket Tools Thread Business_Logic Message)
endif()