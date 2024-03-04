add_library(Database
        Repository.cpp)

add_subdirectory(Tables)
add_subdirectory(DataMappers)
add_subdirectory(Pool)
add_subdirectory(Database_Handlers)

target_link_libraries(Database PUBLIC Tables DataMappers Pool Database_Handlers)
