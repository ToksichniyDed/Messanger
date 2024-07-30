cmake_minimum_required(VERSION 3.26)
project(Server)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS json REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(libpqxx REQUIRED)

#set(PQXX_INCLUDE_DIRS ${PQXX_INCLUDE_DIRS} CACHE STRING "libpqxx include directories")
#set(PQXX_LINK_LIBRARIES ${PQXX_LIBRARIES} CACHE STRING "libpqxx link libraries")
#include_directories(${PQXX_INCLUDE_DIRS})

include_directories(${PostgreSQL_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

add_subdirectory(Modules)
#add_subdirectory(Tests)

add_executable(Server main.cpp
)

target_link_libraries(Server PRIVATE Modules)
target_include_directories(Server PUBLIC ${Boost_INCLUDE_DIRS})
