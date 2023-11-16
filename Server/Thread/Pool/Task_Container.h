//
// Created by super on 15.11.2023.
//

#ifndef SERVER_TASK_CONTAINER_H
#define SERVER_TASK_CONTAINER_H

#include <winsock2.h>

#include "../../Tools/Containers/TContainer_Queue.h"
#include "../../Business_Logic/Task/Task.h"

class Task_Container {
private:
    TContainer_Queue<Task*> m_task_queue;

public:
    void Emplace_Task(Task* task);
    void Pop_Task();
    Task* Front_Task();
    void Notify_All();
    void Notify_One();
    bool Empty();
    int Size();
    void Condition(std::function<bool()> condition);
};


#endif //SERVER_TASK_CONTAINER_H
