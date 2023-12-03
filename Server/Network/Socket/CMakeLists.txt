add_library(Socket Client_Manager.cpp
Client_Socket/Client_Socket_Manager.cpp
Client_Socket/Client_Socket.cpp
Server_Socket/Server_Socket.cpp)

target_link_libraries(Socket ws2_32 Tools Thread)