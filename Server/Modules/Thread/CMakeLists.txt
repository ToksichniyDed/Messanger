add_library(Thread Thread.cpp
        Pool/Thread_Pool.cpp
        Pool/Task_Container.cpp)

target_link_libraries(Thread Tools Business_Logic)