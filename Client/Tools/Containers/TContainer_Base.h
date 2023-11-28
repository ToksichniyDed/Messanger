//
// Created by super on 13.11.2023.
//

#ifndef SERVER_TCONTAINER_BASE_H
#define SERVER_TCONTAINER_BASE_H


#include <queue>
#include <functional>

#include "../Synchronized/Mutex.h"
#include "../Synchronized/Conditional_Variable.h"


template<typename Container_Type, typename Data_Type>
class TContainer_Base {
protected:
    Container_Type m_container;
    Mutex m_mutex;
    Conditional_Variable m_cv;

public:
    int Size();
    bool Empty();
    void Notify_One();
    void Notify_All();
    void Conditional(std::function<bool()> &function);
    void Clear(Data_Type &data);
};

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Notify_All() {
    m_cv.Notify_All();
}

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Conditional(std::function<bool()> &function) {
    m_cv.Wait(m_mutex.Get_Unique_Lock(), function);
}

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Notify_One() {
    m_cv.Notify_One();
}

template<typename Container_Type, typename Data_Type>
int TContainer_Base<Container_Type, Data_Type>::Size() {
    m_mutex.Get_Unique_Lock();
    int size = m_container.size();
    return size;
}

template<typename Container_Type, typename Data_Type>
bool TContainer_Base<Container_Type, Data_Type>::Empty() {
    m_mutex.Get_Unique_Lock();
    bool status = m_container.empty();
    return status;
}

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Clear(Data_Type &data) {
    m_mutex.Get_Unique_Lock();
    m_container.clear();
}


#endif //SERVER_TCONTAINER_BASE_H
