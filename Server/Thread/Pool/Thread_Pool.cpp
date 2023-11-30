//
// Created by super on 15.11.2023.
//

#include "Thread_Pool.h"


//Создание потоков
Thread_Pool::Thread_Pool(int count_of_threads, Task_Container* client_tasks):m_client_tasks(client_tasks) {
    for(int i = 0; i< count_of_threads; ++i)
    {
        Thread* thread = new Thread(m_client_tasks);
        thread->Wait_Task();
        m_thread_pool.Emplace_Back(thread);
    }
}

Thread_Pool::~Thread_Pool() {
    for(int i = 0; i<m_thread_pool.Size(); ++i)
    {
        m_thread_pool.At(i)->Close_Thread();
        delete m_thread_pool.At(i);
    }
}

//Динамичееское расширение пула, если ранее установленное число потоков не справляется с задачами,
//то есть количество задач в очереди задач превышает какое то число.
void Thread_Pool::Add_Thread(int count_of_threads) {
    for(int i = 0; i < count_of_threads; ++i)
    {
        Thread* thread = new Thread(m_client_tasks);
        thread->Wait_Task();
        m_thread_pool.Emplace_Back(thread);
    }
}

//Если созданно избыточное количество потоков, можно разгрузить систему, закрыв несколько потоков
void Thread_Pool::Sub_Thread(int count_of_threads) {
    for(int i = 0; i < count_of_threads; ++i)
    {
        m_thread_pool.At(m_thread_pool.Size()-i)->Close_Thread();
        delete m_thread_pool.At(m_thread_pool.Size()-i);
        m_thread_pool.Erase(m_thread_pool.Size()-i);
    }
}




