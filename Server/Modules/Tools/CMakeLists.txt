add_library(Tools
        Json_Tools.cpp
        OpenSSL_Tools.cpp
)

add_subdirectory(Synchronized)
add_subdirectory(Containers)

target_link_libraries(Tools Synchronized Containers ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})