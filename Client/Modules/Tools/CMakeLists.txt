add_library(Tools
        Json_Tools.cpp
        OpenSSL_Tools.cpp
        TFactory.h
)

add_subdirectory(Synchronized)
add_subdirectory(Containers)

target_include_directories(Tools PRIVATE ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(Tools Synchronized Containers ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})