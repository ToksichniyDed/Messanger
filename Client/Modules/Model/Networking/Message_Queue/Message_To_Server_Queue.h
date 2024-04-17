//
// Created by Toksichniy_Ded on 09.04.2024.
//

#ifndef CLIENT_MESSAGE_TO_SERVER_QUEUE_H
#define CLIENT_MESSAGE_TO_SERVER_QUEUE_H

#include <memory>

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/di.hpp>

#include "../Socket/Message_Type/IMessage.h"

class Message_To_Server_Queue {
public:
    using Message_Ptr = std::shared_ptr<IMessage>;
    using message_queue = boost::lockfree::spsc_queue<Message_Ptr>;
    using queue_ptr = std::shared_ptr<message_queue>;

private:
    queue_ptr m_queue;
    static std::shared_ptr<Message_To_Server_Queue> m_instance;
    explicit Message_To_Server_Queue(queue_ptr queue):m_queue(std::move(queue)){}

public:
    static std::shared_ptr<Message_To_Server_Queue> Instance();
    void Push_Message(Message_Ptr message);
    [[nodiscard]] std::shared_ptr<IMessage> Pop_Message() const;
    bool Empty();
};


#endif //CLIENT_MESSAGE_TO_SERVER_QUEUE_H
