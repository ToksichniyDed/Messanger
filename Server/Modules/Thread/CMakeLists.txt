add_library(Thread Thread.cpp
        Pool/Thread_Pool.cpp)

target_link_libraries(Thread Tools Business_Logic)