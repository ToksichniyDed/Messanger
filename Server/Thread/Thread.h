//
// Created by super on 16.11.2023.
//

#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <thread>
#include <functional>

#include "../Tools/Synchronized/Mutex.h"
#include "../Tools/Synchronized/Conditional_Variable.h"
#include "../Business_Logic/Task/Task.h"
#include "../Thread/Pool/Task_Container.h"

//Класс Thread реализует поток. Поток создается для многопоточного решения клиентских задач.

class Thread {
private:
    std::thread m_thread;
    Task_Container* m_client_tasks;

public:
    Thread(Task_Container* client_tasks);
    void Close_Thread();
    void Take_Task(Task* task);
    void Wait_Task();
};


#endif //SERVER_THREAD_H
