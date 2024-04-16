//
// Created by super on 30.11.2023.
//

#ifndef CLIENT_MESSAGE_FROM_SERVER_QUEUE_H
#define CLIENT_MESSAGE_FROM_SERVER_QUEUE_H

#include <memory>

#include <boost/di.hpp>
#include <boost/lockfree/spsc_queue.hpp>

#include "../Socket/Message_Type/IMessage.h"

class Message_From_Server_Queue {
public:
    using Message_Ptr = std::shared_ptr<IMessage>;
    using message_queue = boost::lockfree::spsc_queue<Message_Ptr>;
    using queue_ptr = std::unique_ptr<message_queue>;

private:
     queue_ptr m_queue;
     static std::shared_ptr<Message_From_Server_Queue> m_instance;
     explicit Message_From_Server_Queue(queue_ptr queue):m_queue(std::move(queue)){}

public:
    static std::shared_ptr<Message_From_Server_Queue> Instance();
    void Push_Message(Message_Ptr message);
    bool Empty();
};


#endif //CLIENT_MESSAGE_FROM_SERVER_QUEUE_H
