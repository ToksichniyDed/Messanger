//
// Created by super on 15.11.2023.
//

#include "Task_Container.h"

#include <utility>

void Task_Container::Emplace_Task(std::unique_ptr<Task> task) {
    m_task_queue.Emplace(std::move(task));
}

void Task_Container::Pop_Task() {
    m_task_queue.Pop();
}

std::unique_ptr<Task> Task_Container::Front_Task() {
    auto ans = std::move(m_task_queue.Front());
    return ans;
}

void Task_Container::Notify_All() {
    m_task_queue.Notify_All();
}

void Task_Container::Condition(std::function<bool()> condition) {
    m_task_queue.Conditional(std::move(condition));
}

void Task_Container::Notify_One() {
    m_task_queue.Notify_One();
}

bool Task_Container::Empty() {
    return m_task_queue.Empty();
}

int Task_Container::Size() {
    return m_task_queue.Size();
}


