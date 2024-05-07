add_library(Tools
        Json_Tools.cpp
        OpenSSL_Tools.cpp
)

target_link_libraries(Tools ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
#target_include_directories(Tools PUBLIC ${Boost_INCLUDE_DIRS}})
include_directories(Containers)