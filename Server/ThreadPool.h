//
// Created by super on 06.09.2023.
//

#ifndef SERVER_THREADPOOL_H
#define SERVER_THREADPOOL_H

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <functional>
#include <queue>

#include "ClientHandler/ClientHandler.h"


class ThreadPool {
private:
    std::vector<std::thread> m_thread_pools;
    std::queue<SOCKET> m_client_queue;
    std::mutex m_access_to_client_queue;
    std::condition_variable m_conditional_variable;

public:
    explicit ThreadPool(int count_of_pools);
    ~ThreadPool();
    void Push_New_Client(SOCKET client_socket);
};


#endif //SERVER_THREADPOOL_H
