add_library(DataMappers UserMapper.cpp PasswordMapper.cpp)

target_link_libraries(DataMappers Tables Database)