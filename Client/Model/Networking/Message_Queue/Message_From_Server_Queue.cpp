//
// Created by super on 30.11.2023.
//

#include "Message_From_Server_Queue.h"

void Message_From_Server_Queue::Add_Message(std::string message) {
    m_message_from_server_queue.Emplace(message);
}

void Message_From_Server_Queue::Pop_Message() {
    m_message_from_server_queue.Pop();
}

std::string Message_From_Server_Queue::Front_Message() {
    std::string temp = m_message_from_server_queue.Front();
    m_message_from_server_queue.Pop();
    return temp;
}

bool Message_From_Server_Queue::Empty() {
    return m_message_from_server_queue.Empty();
}

void Message_From_Server_Queue::Condition(std::function<bool()> function) {
    m_message_from_server_queue.Conditional(function);
}
