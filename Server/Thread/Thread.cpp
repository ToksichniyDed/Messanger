//
// Created by super on 16.11.2023.
//

#include "Thread.h"

Thread::Thread(Task_Container *client_tasks):m_client_tasks(client_tasks) {
}

//Выполнение клиентской задачи
void Thread::Take_Task(Task* task) {
    task->Execute();
}

//Поток стоит на пазуе, пока контейнер клиентских задач пустой.
void Thread::Wait_Task() {
    while(true){
        auto conditional = [&](){return m_client_tasks->Empty();};
        std::cout<<"Thread "<<std::this_thread::get_id() <<" wait client task!"<<std::endl;
        m_client_tasks->Condition(std::move(conditional));
        std::cout << "Thread " << std::this_thread::get_id() << " start handle client task!" << std::endl;
        this->Take_Task(m_client_tasks->Front_Task());
        std::cout<<"Thread "<<std::this_thread::get_id() <<" is free!"<<std::endl;
    }
}

void Thread::Close_Thread() {
    m_thread.join();
}

