//
// Created by super on 13.11.2023.
//

#ifndef SERVER_MUTEX_H
#define SERVER_MUTEX_H

#include <mutex>

class Mutex {
private:
    std::mutex m_mutex;

public:
    void Lock();
    void Unlock();
    std::mutex& Get_Mutex();
};


#endif //SERVER_MUTEX_H
