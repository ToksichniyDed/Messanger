add_subdirectory(Task_Type)

add_library(Task Task_Factory.cpp)

target_link_libraries(Task Task_Type Message)