//
// Created by super on 15.11.2023.
//

#ifndef SERVER_CONTAINER_VECTOR_H
#define SERVER_CONTAINER_VECTOR_H

#include <vector>

#include "TContainer_Base.h"

//Шаблон для контейнера-вектора

template<typename Data_Type>
class Container_Vector : public TContainer_Base<std::vector<Data_Type>, Data_Type> {
public:
    virtual void Emplace_Back(Data_Type &data);
    virtual void Emplace_Back(Data_Type data);
    void Erase(int temp);
    virtual Data_Type &At(int temp);
    Data_Type operator[](int index);
};

template<typename Data_Type>
Data_Type Container_Vector<Data_Type>::operator[](int index) {
    std::unique_lock<std::mutex> lock (this->m_mutex.Get_Mutex());
    return this->m_container[index];
}

template<typename Data_Type>
void Container_Vector<Data_Type>::Emplace_Back(Data_Type data) {
    std::unique_lock<std::mutex> lock (this->m_mutex.Get_Mutex());
    this->m_container.emplace_back(std::move(data));
}

template<typename Data_Type>
Data_Type &Container_Vector<Data_Type>::At(int temp) {
    std::unique_lock<std::mutex> lock (this->m_mutex.Get_Mutex());
    if (temp < this->m_container.size()) {
        Data_Type &ans = this->m_container.at(temp);
        return ans;
    }
    throw std::runtime_error ("Failed find element in Container_Vector.At()!");
}

template<typename Data_Type>
void Container_Vector<Data_Type>::Erase(int temp) {
    std::unique_lock<std::mutex> lock (this->m_mutex.Get_Mutex());
    if (temp < this->m_container.size()) {
        auto it = this->m_container.begin() + temp;
        this->m_container.erase(it);
    }
}

template<typename Data_Type>
void Container_Vector<Data_Type>::Emplace_Back(Data_Type &data) {
    std::unique_lock<std::mutex> lock (this->m_mutex.Get_Mutex());
    this->m_container.emplace_back(std::move(data));
}

#endif //SERVER_CONTAINER_VECTOR_H
