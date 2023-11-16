//
// Created by super on 15.11.2023.
//

#ifndef SERVER_THREAD_POOL_H
#define SERVER_THREAD_POOL_H

#include "Task_Container.h"
#include "../../Tools/Containers/Container_Vector.h"
#include "../Thread.h"

class Thread_Pool {
private:
    Container_Vector<Thread*> m_thread_pool;
    Task_Container* m_client_tasks;

public:
    Thread_Pool(int count_of_threads, Task_Container* client_tasks);
    ~Thread_Pool();
    void Add_Thread(int count_of_threads);
    void Sub_Thread(int count_of_threads);
};


#endif //SERVER_THREAD_POOL_H
