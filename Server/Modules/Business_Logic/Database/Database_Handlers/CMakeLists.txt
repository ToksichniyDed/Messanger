add_library(Database_Handlers User_Handler.cpp
        Password_Handller.cpp)

target_link_libraries(Database_Handlers DataMappers Pool Tables)