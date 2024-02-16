add_library(Database INTERFACE)

add_subdirectory(Tables)
add_subdirectory(DataMappers)
add_subdirectory(Pool)

find_path(LIBPQXX_INCLUDE_DIR NAMES pqxx/pqxx PATHS "$ENV{LIBPQXX_INCLUDE_DIR}")
find_library(LIBPQXX_LIBRARY NAMES pqxx PATHS "$ENV{LIBPQXX_LIBRARY}")

target_link_libraries(Database INTERFACE ${PostgreSQL_LIBRARIES} Tables DataMappers Pool ${LIBPQXX_LIBRARY})
target_include_directories(Database INTERFACE ${LIBPQXX_INCLUDE_DIR})
