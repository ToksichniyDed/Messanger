//
// Created by super on 16.11.2023.
//

#ifndef SERVER_TASK_H
#define SERVER_TASK_H

#include "../../../Tools/Json_Tools.h"
#include "../../Database/Pool/Database_Connector.h"
#include "../../../Network/Socket/Message/include/IMessage.h"


//Интерфейс для классов задач

class Task {
protected:
    Client_Socket* m_socket;
    IMessage* m_message;
    Database_Connector* m_connector;

public:
    Task(Client_Socket* socket = nullptr, IMessage* message = nullptr, Database_Connector* connector = nullptr)
    :m_socket(socket),m_message(message),m_connector(connector){};
    Task() = default;
    virtual ~Task() = default;
    virtual void Execute() = 0;
};


#endif //SERVER_TASK_H
