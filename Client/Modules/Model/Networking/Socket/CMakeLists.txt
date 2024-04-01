add_library(Socket Socket.cpp Socket_Manager.cpp)

add_subdirectory(Message_Type)

target_include_directories(Socket PRIVATE Socket.h Socket_Manager.h)
target_link_libraries(Socket Tools Message_Type)