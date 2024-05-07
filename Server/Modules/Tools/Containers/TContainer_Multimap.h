//
// Created by Toksichniy_Ded on 06.03.2024.
//

#ifndef SERVER_TCONTAINER_MULTIMAP_H
#define SERVER_TCONTAINER_MULTIMAP_H

#include <map>
#include <mutex>
#include <condition_variable>


template<class Key_Type, class Data_Type>
class TContainer_Multimap {
protected:
    std::multimap<Key_Type, Data_Type> m_map;
    std::mutex m_mutex;
    std::condition_variable m_cv;

public:
    virtual void Insert(Key_Type key, Data_Type data);

    virtual void Emplace(Key_Type key, Data_Type data);

    virtual void Erase(Key_Type key);

    virtual Data_Type Find(Key_Type key);

    virtual void Clear();

    virtual bool Empty();

    virtual int Size();
};

template<class Key_Type, class Data_Type>
int TContainer_Multimap<Key_Type, Data_Type>::Size() {
    std::unique_lock<std::mutex> lock (m_mutex);
    return m_map.size();
}

template<class Key_Type, class Data_Type>
void TContainer_Multimap<Key_Type, Data_Type>::Insert(Key_Type key, Data_Type data) {
    std::unique_lock<std::mutex> lock (m_mutex);
    m_map.insert(std::make_pair(key,data));
}

template<class Key_Type, class Data_Type>
void TContainer_Multimap<Key_Type, Data_Type>::Emplace(Key_Type key, Data_Type data) {
    std::unique_lock<std::mutex> lock (m_mutex);
    m_map.emplace(key,data);
}

template<class Key_Type, class Data_Type>
void TContainer_Multimap<Key_Type, Data_Type>::Erase(Key_Type key) {
    std::unique_lock<std::mutex> lock (m_mutex);
    m_map.erase(key);
}

template<class Key_Type, class Data_Type>
Data_Type TContainer_Multimap<Key_Type, Data_Type>::Find(Key_Type key) {
    std::unique_lock<std::mutex> lock (m_mutex);
    auto it = m_map.find(key);
    if(it != m_map.end())
        return it->second;
    return nullptr;
}

template<class Key_Type, class Data_Type>
void TContainer_Multimap<Key_Type, Data_Type>::Clear() {
    std::unique_lock<std::mutex> lock (m_mutex);
    m_map.clear();
}

template<class Key_Type, class Data_Type>
bool TContainer_Multimap<Key_Type, Data_Type>::Empty() {
    std::unique_lock<std::mutex> lock (m_mutex);
    return m_map.empty();
}

#endif //SERVER_TCONTAINER_MULTIMAP_H
