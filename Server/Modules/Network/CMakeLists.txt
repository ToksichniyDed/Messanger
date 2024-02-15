add_library(Network INTERFACE)

add_subdirectory(Socket)
add_subdirectory(Protocols)

target_link_libraries(Network INTERFACE Socket Protocols)