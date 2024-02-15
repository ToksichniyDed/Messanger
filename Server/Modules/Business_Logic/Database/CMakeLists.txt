add_library(Database
        Database_Manager.h
        Database_Manager.cpp
        Database_Connector.h
        Database_Connector.cpp
        Query_Executor.cpp
        Query_Executor.h)

add_subdirectory(Tables)
add_subdirectory(DataMappers)

target_link_libraries(Database ${PostgreSQL_LIBRARIES} Tables DataMappers)