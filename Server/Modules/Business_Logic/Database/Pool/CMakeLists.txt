add_library(Pool Database_Connector.cpp
Pool_Connection.cpp)

target_link_libraries(Pool Database Tools)