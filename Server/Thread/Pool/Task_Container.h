//
// Created by super on 15.11.2023.
//

#ifndef SERVER_TASK_CONTAINER_H
#define SERVER_TASK_CONTAINER_H

#include <winsock2.h>

#include "../../Tools/Containers/TContainer_Queue.h"
#include "../../Business_Logic/Task/Task.h"

//Реализация очереди задач с помощью шаблона-очереди

class Task_Container {
private:
    TContainer_Queue<Task*> m_task_queue;

public:
    virtual void Emplace_Task(Task* task);
    virtual void Pop_Task();
    virtual Task* Front_Task();
    virtual void Notify_All();
    virtual void Notify_One();
    virtual bool Empty();
    virtual int Size();
    virtual void Condition(std::function<bool()> condition);
};


#endif //SERVER_TASK_CONTAINER_H
