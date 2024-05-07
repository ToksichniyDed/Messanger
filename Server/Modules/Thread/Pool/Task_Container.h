//
// Created by Toksichniy_Ded on 07.05.2024.
//

#ifndef SERVER_TASK_CONTAINER_H
#define SERVER_TASK_CONTAINER_H

#include <memory>

#include "../../Business_Logic/Task/include/Task.h"
#include "../../Tools/Containers/TContainer_Queue.h"

class Task_Container: public TContainer_Queue<std::unique_ptr<Task>>{
public:
    virtual std::unique_ptr<Task> Wait_Until_Not_Empty();
};

inline std::unique_ptr<Task> Task_Container::Wait_Until_Not_Empty() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock,[&]{return !m_container.empty();});
    auto task = std::move(m_container.front());
    m_container.pop();
    return task;
}


#endif //SERVER_TASK_CONTAINER_H
