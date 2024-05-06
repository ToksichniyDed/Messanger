//
// Created by super on 15.11.2023.
//

#include "Thread_Pool.h"


//Создание потоков
Thread_Pool::Thread_Pool(int count_of_threads, std::shared_ptr<Task_Container> client_tasks,
                         std::unique_ptr<Thread_Creator> creator,
                         std::unique_ptr<Container_Vector<std::unique_ptr<IThread>>> thread_pool){

    if(client_tasks)
        m_client_tasks = client_tasks;

    if(creator)
        m_creator = std::move(creator);

    if(thread_pool)
        m_thread_pool = std::move(thread_pool);

    if(!((m_client_tasks && m_creator && m_thread_pool) || count_of_threads<=0))
        throw std::runtime_error("Failed create Thread_Pool!");

    Add_Thread(count_of_threads);
}

Thread_Pool::~Thread_Pool() {
    for(int i = 0; i<m_thread_pool->Size(); ++i)
    {
        m_thread_pool->At(i)->Close_Thread();
    }
    m_thread_pool->Clear();
}

//Динамичееское расширение пула, если ранее установленное число потоков не справляется с задачами,
//то есть количество задач в очереди задач превышает какое то число.
void Thread_Pool::Add_Thread(int count_of_threads) {
    for(int i = 0; i < count_of_threads; ++i)
    {
        auto thread = m_creator->Create_Thread(m_client_tasks);
        m_thread_pool->Emplace_Back(std::move(thread));
    }
}

//Если созданно избыточное количество потоков, можно разгрузить систему, закрыв несколько потоков
void Thread_Pool::Sub_Thread(int count_of_threads) {
    for(int i = 0; i < count_of_threads && m_thread_pool->Size() > i; ++i)
    {
        m_thread_pool->At(m_thread_pool->Size() - 1 - i)->Close_Thread();
        m_thread_pool->Erase(m_thread_pool->Size() - 1 - i);
    }
}




