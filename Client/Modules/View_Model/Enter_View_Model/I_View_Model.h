//
// Created by Toksichniy_Ded on 02.05.2024.
//

#ifndef CLIENT_I_VIEW_MODEL_H
#define CLIENT_I_VIEW_MODEL_H

#include <memory>

#include "../../Model/Networking/Message_Queue/Message_From_Server_Queue.h"
#include "../../Model/Networking/Socket/Socket.h"

class I_View_Model {
public:
    using Socket_Ptr = std::shared_ptr<Socket>;
    using Queue_Ptr = std::shared_ptr<Message_From_Server_Queue>;

protected:
    Socket_Ptr m_socket;
    Queue_Ptr m_queue;


public:
    explicit I_View_Model():m_socket(Socket::Instance()), m_queue(Message_From_Server_Queue::Instance()){};
    virtual ~I_View_Model() = default;
};

#endif //CLIENT_I_VIEW_MODEL_H