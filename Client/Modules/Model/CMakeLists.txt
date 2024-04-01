add_library(Model INTERFACE)

add_subdirectory(Networking)

target_link_libraries(Model INTERFACE Networking)