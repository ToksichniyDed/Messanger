//
// Created by super on 30.11.2023.
//

#include "Message_From_Server_Queue.h"

std::shared_ptr<Message_From_Server_Queue> Message_From_Server_Queue::m_instance = nullptr;

bool Message_From_Server_Queue::Empty() {
    return m_queue->empty();
}

void Message_From_Server_Queue::Push_Message(Message_From_Server_Queue::Message_Ptr message) {
    m_queue->push(message);
}

std::shared_ptr<Message_From_Server_Queue> Message_From_Server_Queue::Instance() {
    if(!m_instance){
        auto queue = std::make_unique<message_queue>();
    }
    return m_instance;
}
