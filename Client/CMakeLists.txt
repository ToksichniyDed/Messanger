cmake_minimum_required(VERSION 3.26)
project(Client)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Client main.cpp
        #Tools
        Tools/Json_Tools.cpp
        Tools/Json_Tools.h
        Tools/Containers/Container_Vector.h
        Tools/Containers/TContainer_Base.h
        Tools/Containers/TContainer_Queue.h
        Tools/Synchronized/Conditional_Variable.h
        Tools/Synchronized/Conditional_Variable.cpp
        Tools/Synchronized/Mutex.h
        Tools/Synchronized/Mutex.cpp

        #Model
        Model/Networking/Socket/Socket_Manager.cpp
        Model/Networking/Socket/Socket_Manager.h
        Model/Networking/Socket/Socket.cpp
        Model/Networking/Socket/Socket.h
        Model/Networking/Message_Queue/Message_From_Server_Queue.cpp
        Model/Networking/Message_Queue/Message_From_Server_Queue.h

        #View
        View/Authentication_View/Login.h
        View_Model/Authentication_View_Model/Authorization_Data.cpp
        View_Model/Authentication_View_Model/Authentication_Data.h
        View_Model/Authentication_View_Model/Registration_Data.cpp
        View_Model/Authentication_View_Model/Registration_Data.h
)

target_link_libraries(Client PRIVATE ws2_32.lib ${Boost_LIBRARIES})
