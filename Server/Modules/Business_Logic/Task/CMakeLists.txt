add_subdirectory(Task_Type)

add_library(Task Task_Factory.cpp)

target_link_libraries(Task Task_Type Message)
target_include_directories(Task PRIVATE ${CMAKE_INCLUDE_CURRENT_DIR}/include)