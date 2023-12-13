add_library(NetworkTest INTERFACE)

add_subdirectory(SocketTest)
add_subdirectory(ProtocolsTest)

target_link_libraries(NetworkTest INTERFACE)