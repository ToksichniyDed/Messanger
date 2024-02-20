add_subdirectory(Protocols_Type)
add_subdirectory(Message)

add_library(Protocols INTERFACE)

target_link_libraries(Protocols INTERFACE Protocols_Type Message)