//
// Created by super on 13.11.2023.
//

#include "Mutex.h"

void Mutex::Lock() {
    m_mutex.lock();
}

void Mutex::Unlock() {
    m_mutex.unlock();
}

std::mutex& Mutex::Get_Mutex() {
    return m_mutex;
}


