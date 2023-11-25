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
        Network/Socket/ISocket.h
        Network/Socket/Server_Socket/Server_Socket.h
        Network/Socket/Server_Socket/Server_Socket.cpp
        Network/Socket/Client_Socket/Client_Socket_Manager.h
        Network/Socket/Client_Socket/Client_Socket_Manager.cpp
        Tools/Containers/TContainer_Base.h
        Tools/Synchronized/Mutex.cpp
        Tools/Synchronized/Mutex.h
        Tools/Synchronized/Conditional_Variable.cpp
        Tools/Synchronized/Conditional_Variable.h
        Tools/Containers/TContainer_Queue.h
        Tools/Containers/Container_Vector.h
        Network/Socket/Client_Manager.cpp
        Network/Socket/Client_Manager.h
        Thread/Pool/Thread_Pool.cpp
        Thread/Pool/Thread_Pool.h
        Thread/Pool/Task_Container.cpp
        Thread/Pool/Task_Container.h
        Thread/Thread.cpp
        Thread/Thread.h
        Business_Logic/Task/Task.h
        Business_Logic/Task/Task_Factory.cpp
        Business_Logic/Task/Task_Factory.h
        Business_Logic/Task/Task_Type/Registration_Task.cpp
        Business_Logic/Task/Task_Type/Registration_Task.h
        Business_Logic/Task/Task_Type/Authorization_Task.cpp
        Business_Logic/Task/Task_Type/Authorization_Task.h
        Business_Logic/Database/Database_Connector.cpp
        Business_Logic/Database/Database_Connector.h
        Business_Logic/Database/Query_Executor.cpp
        Business_Logic/Database/Query_Executor.h
        Business_Logic/Database/Database_Manager.cpp
        Business_Logic/Database/Database_Manager.h
        Network/Protocols/IMessage_Builder.h
        Network/Protocols/Protocols_Type/Authorization_Message.cpp
        Network/Protocols/Protocols_Type/Authorization_Message.h
        Network/Protocols/Protocols_Type/Registration_Message.cpp
        Network/Protocols/Protocols_Type/Registration_Message.h
        Network/Socket/Client_Socket/Client_Socket.cpp
        Network/Socket/Client_Socket/Client_Socket.h
)

target_link_libraries(Server PRIVATE ws2_32.lib ${Boost_LIBRARIES} ${PostgreSQL_LIBRARIES})
