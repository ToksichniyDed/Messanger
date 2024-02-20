add_library(Database INTERFACE
        Repository.cpp)

add_subdirectory(Tables)
add_subdirectory(DataMappers)
add_subdirectory(Pool)
add_subdirectory(Database_Handlers)

find_path(LIBPQXX_INCLUDE_DIR NAMES pqxx/pqxx PATHS "$ENV{LIBPQXX_INCLUDE_DIR}")
find_library(LIBPQXX_LIBRARY NAMES pqxx PATHS "$ENV{LIBPQXX_LIBRARY}")

target_link_libraries(Database INTERFACE ${PostgreSQL_LIBRARIES} Tables DataMappers Pool Database_Handlers ${LIBPQXX_LIBRARY})
target_include_directories(Database INTERFACE ${LIBPQXX_INCLUDE_DIR})
