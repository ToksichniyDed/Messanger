//
// Created by super on 30.11.2023.
//

#include "Message_From_Server_Queue.h"

bool Message_From_Server_Queue::Empty() {
    return m_queue->empty();
}

void Message_From_Server_Queue::Push_Message(Message_From_Server_Queue::Message_Ptr message) {
    m_queue->push(message);
}
