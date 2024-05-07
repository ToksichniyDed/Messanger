//
// Created by super on 13.11.2023.
//

#ifndef SERVER_TCONTAINER_BASE_H
#define SERVER_TCONTAINER_BASE_H

#include <functional>
#include <string>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <utility>

//Шаблон для контейнеров вместе с мьютексом и условной переменной.
//Тут реализованны основные функции, встречающиеся у каждого вида контейнеров

template<typename Container_Type, typename Data_Type>
class TContainer_Base {
protected:
    Container_Type m_container;
    std::mutex m_mutex;
    std::condition_variable m_cv;

public:
    virtual int Size();
    virtual bool Empty();
    virtual void Notify_One();
    virtual void Notify_All();
    void Clear();
};

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Notify_All() {
    m_cv.notify_all();
}

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Notify_One() {
    m_cv.notify_one();
}

template<typename Container_Type, typename Data_Type>
int TContainer_Base<Container_Type, Data_Type>::Size() {
    std::unique_lock<std::mutex> lock (m_mutex);
    return m_container.size();
}

template<typename Container_Type, typename Data_Type>
bool TContainer_Base<Container_Type, Data_Type>::Empty() {
    std::unique_lock<std::mutex> lock (m_mutex);
    return m_container.empty();
}

template<typename Container_Type, typename Data_Type>
void TContainer_Base<Container_Type, Data_Type>::Clear() {
    std::unique_lock<std::mutex> lock (m_mutex);
    m_container.clear();
}


#endif //SERVER_TCONTAINER_BASE_H
