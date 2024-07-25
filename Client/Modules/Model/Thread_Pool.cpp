//
// Created by Toksichniy_Ded on 09.05.2024.
//

#include "Thread_Pool.h"

Thread_Pool::thread_pool Thread_Pool::Instance(int count) {
    if(!m_thread_pool) {
        m_thread_pool = std::make_shared<boost::asio::thread_pool>(count);
    }
    return m_thread_pool;
}

void Thread_Pool::Push_Task(boost::function<bool()> function) {
    boost::asio::post(*m_thread_pool, function);
}
