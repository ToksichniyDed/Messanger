add_library(View Main_View.cpp)

add_subdirectory(Chats_View)

target_link_libraries(View Chats_View)
target_include_directories(View PRIVATE Enter_View)


