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
    std::vector<SOCKET> m_client_queue;
    std::queue<std::pair<SOCKET,std::vector<char>>> m_received_messages_from_clients;
    std::mutex m_access_to_client_queue;
    std::mutex m_access_to_clients_tasks;
    std::condition_variable m_conditional_variable;

public:
    explicit ThreadPool(int count_of_pools);
    ~ThreadPool();
    void Push_New_Client(SOCKET client_socket);
    void Listening_Connected_Clients();
    void Handlers_Threads();
};

#endif //SERVER_THREADPOOL_H
