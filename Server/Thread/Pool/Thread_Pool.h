//
// Created by super on 15.11.2023.
//

#ifndef SERVER_THREAD_POOL_H
#define SERVER_THREAD_POOL_H

#include "Task_Container.h"
#include "../../Tools/Containers/Container_Vector.h"
#include "../Thread.h"

//Пул потоков держит открытыми заданное число потоков.

class Thread_Pool {
protected:
    Container_Vector<IThread*>* m_thread_pool;
    Task_Container* m_client_tasks;
    Thread_Creator* m_creator;

public:
    Thread_Pool(int count_of_threads, Task_Container* client_tasks, Thread_Creator* creator, Container_Vector<IThread*>* thread_pool);
    virtual ~Thread_Pool();
    void Add_Thread(int count_of_threads);
    void Sub_Thread(int count_of_threads);
};

class Real_Thread_Creator : public Thread_Creator {
private:
    Thread* thread;
public:
    IThread* Create_Thread(Task_Container* task_container) override{
        thread = new Thread(task_container);
        return thread;
    }
    ~Real_Thread_Creator() override{
        delete thread;
    }
};

#endif //SERVER_THREAD_POOL_H
