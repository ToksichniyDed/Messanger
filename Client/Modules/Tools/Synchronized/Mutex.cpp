//
// Created by super on 13.11.2023.
//

#include "Mutex.h"

Mutex &Mutex::Lock() {
    m_mutex.lock();
    return *this;
}

Mutex &Mutex::Unlock() {
    m_mutex.unlock();
    return *this;
}

std::unique_lock<std::mutex> Mutex::Get_Unique_Lock() {
    return std::unique_lock<std::mutex>(m_mutex);
}

