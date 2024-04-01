//
// Created by super on 30.11.2023.
//

#ifndef CLIENT_MESSAGE_FROM_SERVER_QUEUE_H
#define CLIENT_MESSAGE_FROM_SERVER_QUEUE_H

#include <memory>

#include <boost/lockfree/spsc_queue.hpp>

#include "../Socket/Message_Type/IMessage.h"

class Message_From_Server_Queue {
public:
    using Message_Ptr = std::shared_ptr<IMessage>;
    using message_queue = boost::lockfree::spsc_queue<Message_Ptr>;
    using queue_ptr = std::unique_ptr<message_queue>;

private:
     queue_ptr m_queue;

public:
    explicit Message_From_Server_Queue(queue_ptr queue){}
    void Push_Message(Message_Ptr message);
    bool Empty();
};


#endif //CLIENT_MESSAGE_FROM_SERVER_QUEUE_H
