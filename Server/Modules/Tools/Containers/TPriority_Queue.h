//
// Created by Toksichniy_Ded on 07.03.2024.
//

#ifndef SERVER_TPRIORITY_QUEUE_H
#define SERVER_TPRIORITY_QUEUE_H

#include <queue>

#include "TContainer_Base.h"

template<typename Data_Type>
class TPriority_Queue : public TContainer_Base<std::priority_queue<Data_Type>, Data_Type> {
public:
    virtual void Push(Data_Type data);
    virtual void Pop();
    virtual Data_Type Top();
};

template<typename Data_Type>
Data_Type TPriority_Queue<Data_Type>::Top() {
    std::unique_lock<std::mutex> lock (this->m_mutex);
    if(this->m_container.empty())
        return Data_Type();
    auto temp = std::move(this->m_container.top());
    return temp;
}

template<typename Data_Type>
void TPriority_Queue<Data_Type>::Pop() {
    std::unique_lock<std::mutex> lock (this->m_mutex);
    if(this->m_container.empty())
        return;
    this->m_container.pop();
}

template<typename Data_Type>
void TPriority_Queue<Data_Type>::Push(Data_Type data) {
    std::unique_lock<std::mutex> lock (this->m_mutex);
    this->m_container.push(std::move(data));
}

#endif //SERVER_TPRIORITY_QUEUE_H
