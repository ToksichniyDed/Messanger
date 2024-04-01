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
    Mutex &Lock();
    Mutex &Unlock();
    std::unique_lock<std::mutex> Get_Unique_Lock();
};


#endif //SERVER_MUTEX_H
