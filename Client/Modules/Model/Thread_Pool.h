//
// Created by Toksichniy_Ded on 09.05.2024.
//

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include<memory>
#include <boost/asio.hpp>
#include <boost/function.hpp>

class Thread_Pool {
public:
    using thread_pool = std::shared_ptr<boost::asio::thread_pool>;

protected:
    static thread_pool m_thread_pool;
    explicit Thread_Pool(int count){}

public:
    ~Thread_Pool() {
        m_thread_pool->join();
    }
    static thread_pool Instance(int count);
    static void Push_Task(boost::function<bool()> function);

};



#endif //THREAD_POOL_H
