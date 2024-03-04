find_path(LIBPQXX_INCLUDE_DIR NAMES pqxx/pqxx PATHS "$ENV{LIBPQXX_INCLUDE_DIR}")
find_library(LIBPQXX_LIBRARY NAMES pqxx PATHS "$ENV{LIBPQXX_LIBRARY}")

add_library(Pool Database_Connector.cpp
Pool_Connection.cpp)

target_link_libraries(Pool PRIVATE Tools ${LIBPQXX_LIBRARY} ${PostgreSQL_LIBRARY} ws2_32)
target_include_directories(Pool PRIVATE ${LIBPQXX_INCLUDE_DIR})

