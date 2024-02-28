add_library(Database_Handlers User_Handler.cpp
        Password_Handler.cpp)

target_link_libraries(Database_Handlers DataMappers Pool Tables)
target_include_directories(Database_Handlers PRIVATE ${CMAKE_INCLUDE_CURRENT_DIR}/include)