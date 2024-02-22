add_library(Task_Type Registration_Task.cpp
        Authorization_Task.cpp)

target_link_libraries(Task_Type Tools Database Network)
target_include_directories(Task_Type PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)