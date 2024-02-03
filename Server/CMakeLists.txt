cmake_minimum_required(VERSION 3.26)
project(Server)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PostgreSQL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PostgreSQL_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

add_subdirectory(Business_Logic)
add_subdirectory(Network)
add_subdirectory(Tools)
add_subdirectory(Thread)
add_subdirectory(Tests)

add_executable(Server main.cpp
)

target_link_libraries(Server PRIVATE Thread PRIVATE Tools PRIVATE Network PRIVATE Business_Logic PRIVATE Tests)
