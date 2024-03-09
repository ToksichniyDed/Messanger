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
    virtual void Emplace_Back(Data_Type &&data);
    void Erase(int temp);
    virtual Data_Type &At(int temp);
    Data_Type operator[](int index);
};

template<typename Data_Type>
Data_Type Container_Vector<Data_Type>::operator[](int index) {
    auto mutex = this->m_mutex.Get_Unique_Lock();
    return this->m_container[index];
}

template<typename Data_Type>
void Container_Vector<Data_Type>::Emplace_Back(Data_Type &&data) {
    auto mutex = this->m_mutex.Get_Unique_Lock();
    this->m_container.emplace_back(std::forward<Data_Type>(data));
}

template<typename Data_Type>
Data_Type &Container_Vector<Data_Type>::At(int temp) {
    if (temp < this->Size()) {
        auto mutex = this->m_mutex.Get_Unique_Lock();
        Data_Type &ans = this->m_container.at(temp);
        return ans;
    }
}

template<typename Data_Type>
void Container_Vector<Data_Type>::Erase(int temp    ) {
    if (temp < this->Size()) {
        auto mutex = this->m_mutex.Get_Unique_Lock();
        auto it = this->m_container.begin() + temp;
        this->m_container.erase(it);
    }
}

template<typename Data_Type>
void Container_Vector<Data_Type>::Emplace_Back(Data_Type &data) {
    auto mutex = this->m_mutex.Get_Unique_Lock();
    this->m_container.emplace_back(data);
}

#endif //SERVER_CONTAINER_VECTOR_H
