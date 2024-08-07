//
// Created by super on 16.11.2023.
//

#include "Thread.h"


Thread::Thread(std::shared_ptr<Task_Container> client_tasks) {
    if(client_tasks)
        m_client_tasks = client_tasks;

    m_thread = std::make_unique<std::thread>([this]{this->Wait_Task();});

    if(!(m_client_tasks && m_thread))
        throw std::runtime_error("Failed create Thread!");
}

//Выполнение клиентской задачи
void Thread::Take_Task(std::unique_ptr<Task> task) {
    task->Execute();
}

//Поток стоит на паузе, пока контейнер клиентских задач пустой.
void Thread::Wait_Task() {
    while(!m_should_exit) {
        std::cout << "Thread " << std::this_thread::get_id() << " wait client task!" << std::endl;
        auto task = std::move(m_client_tasks->Wait_Until_Not_Empty());

        if (m_should_exit) {
            break;  // Если флаг установлен, выходим из цикла
        }

        std::cout << "Thread " << std::this_thread::get_id() << " start handle client task!" << std::endl;
        this->Take_Task(std::move(task));
        std::cout << "Thread " << std::this_thread::get_id() << " is free!" << std::endl;
    }
}

void Thread::Close_Thread() {
    m_should_exit = true;
}

Thread::~Thread() {
    m_thread->join();
}
