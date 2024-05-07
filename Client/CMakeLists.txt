cmake_minimum_required(VERSION 3.26)
project(Client)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS thread json REQUIRED )
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(Modules)

add_executable(Client main.cpp)

target_link_libraries(Client PUBLIC Modules ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
target_include_directories(Client PUBLIC ${OPENSSL_INCLUDE_DIRS})

