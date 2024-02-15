//
// Created by super on 15.11.2023.
//

#include "Thread_Pool.h"


//Создание потоков
Thread_Pool::Thread_Pool(int count_of_threads, Task_Container* client_tasks, Thread_Creator* creator, Container_Vector<IThread*>* thread_pool)
:m_client_tasks(client_tasks), m_creator(creator), m_thread_pool(thread_pool) {
    Add_Thread(count_of_threads);
}

Thread_Pool::~Thread_Pool() {
    for(int i = 0; i<m_thread_pool->Size(); ++i)
    {
        m_thread_pool->At(i)->Close_Thread();
        delete m_thread_pool->At(i);
    }
    m_thread_pool->Clear();
}

//Динамичееское расширение пула, если ранее установленное число потоков не справляется с задачами,
//то есть количество задач в очереди задач превышает какое то число.
void Thread_Pool::Add_Thread(int count_of_threads) {
    for(int i = 0; i < count_of_threads; ++i)
    {
        IThread* thread = m_creator->Create_Thread(m_client_tasks);
        thread->Wait_Task();
        m_thread_pool->Emplace_Back(thread);
    }
}

//Если созданно избыточное количество потоков, можно разгрузить систему, закрыв несколько потоков
void Thread_Pool::Sub_Thread(int count_of_threads) {
    for(int i = 0; i < count_of_threads && m_thread_pool->Size() > i; ++i)
    {
        m_thread_pool->At(m_thread_pool->Size() - 1 - i)->Close_Thread();
        delete m_thread_pool->At(m_thread_pool->Size() - 1 - i);
        m_thread_pool->Erase(m_thread_pool->Size() - 1 - i);
    }
}




