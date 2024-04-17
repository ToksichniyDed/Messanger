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
        auto sh_queue = std::make_shared<message_queue>(100);
        auto instance = new Message_From_Server_Queue(sh_queue);
        m_instance = std::shared_ptr<Message_From_Server_Queue>(instance);
    }
    return m_instance;
}
