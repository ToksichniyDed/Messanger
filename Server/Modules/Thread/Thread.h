//
// Created by super on 16.11.2023.
//

#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <thread>
#include <functional>
#include <memory>


#include "../Business_Logic/Task/include/Task.h"
#include "Pool/Task_Container.h"

//Класс интерфейс потока
class IThread {
public:
    virtual void Close_Thread() = 0;
    virtual void Take_Task(std::unique_ptr<Task> task) = 0;
    virtual void Wait_Task() = 0;
    virtual ~IThread() = default;
};

//Фабрика потоков
class Thread_Creator{
public:
    Thread_Creator() = default;
    virtual std::unique_ptr<IThread> Create_Thread(std::shared_ptr<Task_Container> task_container) = 0;
    virtual ~Thread_Creator() = default;
};

//Класс Thread реализует поток. Поток создается для многопоточного решения клиентских задач.
//m_client_tasks хранит указатель на контейнер задач, инициализируется при создании потока
class Thread: public IThread {
protected:
    bool m_should_exit = false;
    std::unique_ptr<std::thread> m_thread;
    std::shared_ptr<Task_Container> m_client_tasks;

public:
    explicit Thread(std::shared_ptr<Task_Container> client_tasks);
    ~Thread() override;
    void Close_Thread() override;
    void Take_Task(std::unique_ptr<Task> task) override;
    void Wait_Task() override;
};


#endif //SERVER_THREAD_H
