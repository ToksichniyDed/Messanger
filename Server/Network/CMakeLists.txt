add_subdirectory(Socket)
add_subdirectory(Protocols)

add_library(Network INTERFACE)

target_link_libraries(Network INTERFACE Socket Protocols)