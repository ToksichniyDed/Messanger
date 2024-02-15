//
// Created by super on 15.11.2023.
//

#ifndef SERVER_TCONTAINER_QUEUE_H
#define SERVER_TCONTAINER_QUEUE_H

#include <queue>

#include "TContainer_Base.h"

//Шаблон для контейнера-очереди

template<typename Data_Type>
class TContainer_Queue : public TContainer_Base<std::queue<Data_Type>, Data_Type> {

public:
    void Emplace(Data_Type &data);
    void Emplace(Data_Type &&data);
    void Pop();
    Data_Type Front();
};

template<typename Data_Type>
void TContainer_Queue<Data_Type>::Emplace(Data_Type &&data) {
    this->m_mutex.Get_Unique_Lock();
    this->m_container.emplace(std::forward<Data_Type>(data));
}

template<typename Data_Type>
Data_Type TContainer_Queue<Data_Type>::Front() {
    Data_Type temp;
    if (!this->Empty()) {
        this->m_mutex.Get_Unique_Lock();
        temp = this->m_container.front();
    }
    return temp;
}

template<typename Data_Type>
void TContainer_Queue<Data_Type>::Pop() {
    if (!this->Empty()) {
        this->m_mutex.Get_Unique_Lock();
        this->m_container.emplace();
    }
}

template<typename Data_Type>
void TContainer_Queue<Data_Type>::Emplace(Data_Type &data) {
    this->m_mutex.Get_Unique_Lock();
    this->m_container.emplace(data);
}




#endif //SERVER_TCONTAINER_QUEUE_H
