//
// Created by Toksichniy_Ded on 09.04.2024.
//

#include "Message_To_Server_Queue.h"

std::shared_ptr<Message_To_Server_Queue> Message_To_Server_Queue::m_instance = nullptr;

void Message_To_Server_Queue::Push_Message(Message_To_Server_Queue::Message_Ptr message) {
    m_queue->push(message);
}

bool Message_To_Server_Queue::Empty() {
    return m_queue->empty();
}

std::shared_ptr<Message_To_Server_Queue> Message_To_Server_Queue::Instance() {
    if(!m_instance){
        auto sh_queue = std::make_shared<message_queue>(100);
        auto instance = new Message_To_Server_Queue(sh_queue);
        m_instance = std::shared_ptr<Message_To_Server_Queue>(instance);
    }
    return m_instance;
}

std::shared_ptr<IMessage> Message_To_Server_Queue::Pop_Message() const {
    auto message = m_queue->front();
    m_queue->pop();
    return message;
}
