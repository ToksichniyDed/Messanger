//
// Created by super on 15.11.2023.
//

#ifndef SERVER_THREAD_POOL_H
#define SERVER_THREAD_POOL_H


#include "../../Tools/Containers/Container_Vector.h"
#include "../../Tools/Containers/TContainer_Queue.h"
#include "../Thread.h"

//Пул потоков держит открытыми заданное число потоков.

class Thread_Pool {
protected:
    std::unique_ptr<Container_Vector<std::unique_ptr<IThread>>> m_thread_pool = nullptr;
    std::shared_ptr<Task_Container> m_client_tasks = nullptr;
    std::unique_ptr<Thread_Creator> m_creator = nullptr;

public:
    explicit Thread_Pool(int count_of_threads, std::shared_ptr<Task_Container> client_tasks,
                std::unique_ptr<Thread_Creator> creator,
                std::unique_ptr<Container_Vector<std::unique_ptr<IThread>>> thread_pool);
    virtual ~Thread_Pool();
    void Add_Thread(int count_of_threads);
    void Sub_Thread(int count_of_threads);
};

class Real_Thread_Creator : public Thread_Creator {
public:
    std::unique_ptr<IThread> Create_Thread(std::shared_ptr<Task_Container> task_container) override{
        return std::make_unique<Thread>(task_container);;
    }
};

#endif //SERVER_THREAD_POOL_H
