add_library(Pool Database_Connector.cpp
        Pool_Connection.cpp)

# Установка переменных для подключения к базе данных
set(DB_USER "postgres" CACHE STRING "Database user name")
set(DB_PASSWORD "password" CACHE STRING "Database password")
set(DB_PORT "5432" CACHE STRING "Database port")
if (UNIX)
    set(DB_HOST "host.docker.internal" CACHE STRING "Database host")
    message(STATUS "Database host address: ${DB_HOST}")
elseif (WIN32)
    set(DB_HOST "localhost" CACHE STRING "Database host")
else()
    set(DB_HOST "localhost" CACHE STRING "Database host")
endif()

# Передача переменных в качестве определений препроцессора
add_compile_definitions(DB_USER="${DB_USER}" DB_PASSWORD="${DB_PASSWORD}" DB_HOST="${DB_HOST}" DB_PORT="${DB_PORT}")

if(WIN32)
    target_link_libraries(Pool PUBLIC Tools ${PQXX_LINK_LIBRARIES} ${PostgreSQL_LIBRARY} ws2_32)
else()
    target_link_libraries(Pool PUBLIC Tools ${PQXX_LINK_LIBRARIES} ${PostgreSQL_LIBRARY})
endif()
#target_include_directories(Pool PUBLIC ${PQXX_INCLUDE_DIRS})



