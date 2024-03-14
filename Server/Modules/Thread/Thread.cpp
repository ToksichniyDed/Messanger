//
// Created by super on 16.11.2023.
//

#include "Thread.h"

Thread::Thread(std::shared_ptr<Task_Container> client_tasks) {
    if(client_tasks)
        m_client_tasks = std::move(client_tasks);
    else
        m_client_tasks = std::make_shared<Task_Container>();

    m_thread = std::make_unique<std::thread>([this]{this->Wait_Task();});
}

//Выполнение клиентской задачи
void Thread::Take_Task(std::unique_ptr<Task> task) {
    task->Execute();
}

//Поток стоит на паузе, пока контейнер клиентских задач пустой.
void Thread::Wait_Task() {
    while(!m_should_exit) {
        auto conditional = [&]() { return m_client_tasks->Empty(); };
        std::cout << "Thread " << std::this_thread::get_id() << " wait client task!" << std::endl;
        m_client_tasks->Condition(std::move(conditional));

        if (m_should_exit) {
            break;  // Если флаг установлен, выходим из цикла
        }

        std::cout << "Thread " << std::this_thread::get_id() << " start handle client task!" << std::endl;
        this->Take_Task(m_client_tasks->Front_Task());
        std::cout << "Thread " << std::this_thread::get_id() << " is free!" << std::endl;
    }
}

void Thread::Close_Thread() {
    m_should_exit = true;
}

Thread::~Thread() {
    m_thread->join();
}
