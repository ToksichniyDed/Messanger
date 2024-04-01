add_library(Networking INTERFACE)

add_subdirectory(Message_Queue)
#add_subdirectory(Protocols)
add_subdirectory(Socket)

target_link_libraries(Networking INTERFACE Message_Queue Socket)