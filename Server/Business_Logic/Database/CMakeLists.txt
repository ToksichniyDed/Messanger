add_library(Database
Database_Manager.h
Database_Manager.cpp
Database_Connector.h
Database_Connector.cpp
Query_Executor.cpp
Query_Executor.h)

find_package(PostgreSQL REQUIRED)

target_link_libraries(Database ${PostgreSQL_LIBRARIES})