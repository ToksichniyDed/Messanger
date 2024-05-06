//
// Created by super on 13.11.2023.
//

#ifndef SERVER_TCONTAINER_BASE_H
#define SERVER_TCONTAINER_BASE_H

#include <functional>
#include <string>
#include <iostream>
#include <thread>

#include "../Synchronized/Mutex.h"
#include "../Synchronized/Conditional_Variable.h"

//Шаблон для контейнеров вместе с мьютексом и условной переменной.
//Тут реализованны основные функции, встречающиеся у каждого вида контейнеров

template<typename Container_Type, typename Data_Type>
class TContainer_Base {
protected:
    Container_Type m_container;
    Mutex m_mutex;
    Conditional_Variable m_cv;

public:
    virtual int Size();
    virtual bool Empty();
    virtual void Notify_One();
    virtual void Notify_All();
    virtual void Conditional(std::function<bool()> function);
    void Clear();
};

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Notify_All() {
    m_cv.Notify_All();
}

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Conditional(std::function<bool()> function) {
    std::unique_lock<std::mutex> lock (m_mutex.Get_Mutex());
    std::cout << "Thread " << std::this_thread::get_id() << " wait client task!" << std::endl;
    m_cv.Wait(lock, std::move(function));
}

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Notify_One() {
    m_cv.Notify_One();
}

template<typename Container_Type, typename Data_Type>
int TContainer_Base<Container_Type, Data_Type>::Size() {
    std::unique_lock<std::mutex> lock (m_mutex.Get_Mutex());
    return m_container.size();
}

template<typename Container_Type, typename Data_Type>
bool TContainer_Base<Container_Type, Data_Type>::Empty() {
    std::unique_lock<std::mutex> lock (m_mutex.Get_Mutex());
    return m_container.empty();
}

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Clear() {
    std::unique_lock<std::mutex> lock (m_mutex.Get_Mutex());
    m_container.clear();
}


#endif //SERVER_TCONTAINER_BASE_H
