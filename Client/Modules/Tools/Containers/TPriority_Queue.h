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
    auto mutex = this->m_mutex.Get_Unique_Lock();
    if(this->Empty())
        return Data_Type();
    return this->m_container.top();
}

template<typename Data_Type>
void TPriority_Queue<Data_Type>::Pop() {
    if(this->Empty())
        return;
    auto mutex = this->m_mutex.Get_Unique_Lock();
    this->m_container.pop();
}

template<typename Data_Type>
void TPriority_Queue<Data_Type>::Push(Data_Type data) {
    auto mutex = this->m_mutex.Get_Unique_Lock();
    this->m_container.push(std::move(data));
}

#endif //SERVER_TPRIORITY_QUEUE_H
