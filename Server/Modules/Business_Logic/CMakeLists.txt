add_subdirectory(Database)
add_subdirectory(Task)

add_library(Business_Logic INTERFACE)

target_link_libraries(Business_Logic INTERFACE Database Task Message Network)