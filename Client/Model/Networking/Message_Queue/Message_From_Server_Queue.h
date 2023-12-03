//
// Created by super on 30.11.2023.
//

#ifndef CLIENT_MESSAGE_FROM_SERVER_QUEUE_H
#define CLIENT_MESSAGE_FROM_SERVER_QUEUE_H

#include <string>

#include "../../../Tools/Containers/TContainer_Queue.h"

class Message_From_Server_Queue {
private:
    TContainer_Queue<std::string> m_message_from_server_queue;

public:
    void Add_Message(std::string message);
    void Pop_Message();
    std::string Front_Message();
    bool Empty();
    void Condition(std::function<bool()> function);
};


#endif //CLIENT_MESSAGE_FROM_SERVER_QUEUE_H
