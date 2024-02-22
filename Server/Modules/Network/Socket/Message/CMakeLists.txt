add_library(Message
        Registration_Message.cpp
        Authorization_Message.cpp)

target_link_libraries(Message Tools)
target_include_directories(Message PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)