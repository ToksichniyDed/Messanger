//
// Created by super on 15.11.2023.
//

#ifndef SERVER_TCONTAINER_QUEUE_H
#define SERVER_TCONTAINER_QUEUE_H

#include <queue>
#include <memory>

#include "TContainer_Base.h"

//Шаблон для контейнера-очереди

template<typename Data_Type>
class TContainer_Queue : public TContainer_Base<std::queue<Data_Type>, Data_Type> {

public:
    void Emplace(Data_Type data);
    void Pop();
    Data_Type Front();
};

template<typename Data_Type>
void TContainer_Queue<Data_Type>::Emplace(Data_Type data) {
    std::unique_lock<std::mutex> lock (this->m_mutex.Get_Mutex());
    this->m_container.emplace(std::move(data));
}

template<typename Data_Type>
Data_Type TContainer_Queue<Data_Type>::Front() {
    std::unique_lock<std::mutex> lock (this->m_mutex.Get_Mutex());
    Data_Type temp;
    if (!this->m_container.empty()) {
        temp = std::move(this->m_container.front());
        this->m_container.pop();
    }

    return std::move(temp);
}

template<typename Data_Type>
void TContainer_Queue<Data_Type>::Pop() {
    std::unique_lock<std::mutex> lock (this->m_mutex.Get_Mutex());
    if (!this->m_container.empty()) {
        this->m_container.pop();
    }
}





#endif //SERVER_TCONTAINER_QUEUE_H
