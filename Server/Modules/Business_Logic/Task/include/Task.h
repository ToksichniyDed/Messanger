//
// Created by super on 16.11.2023.
//

#ifndef SERVER_TASK_H
#define SERVER_TASK_H

#include "../../../Tools/Json_Tools.h"
#include "../../Database/Pool/Database_Connector.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../Database/Repository.h"


//Интерфейс для классов задач

class Task {
protected:
    Client_Socket* m_socket;
    Database_Connector* m_connector;
    Repository* m_repository;

public:
    explicit Task(Client_Socket* socket, Database_Connector* connector, Repository* repository)
    :m_socket(socket),m_connector(connector), m_repository(repository){}
    Task()=default;
    virtual ~Task() = default;
    virtual void Execute() = 0;
};


#endif //SERVER_TASK_H
