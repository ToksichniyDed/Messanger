//
// Created by super on 16.11.2023.
//

#ifndef SERVER_TASK_H
#define SERVER_TASK_H

#include <memory>
#include <utility>

#include "../../../Tools/Json_Tools.h"
#include "../../Database/Pool/Database_Connector.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../Database/Repository.h"


//Интерфейс для классов задач

class Task {
protected:
    std::shared_ptr<Client_Socket> m_socket;
    std::shared_ptr<IDatabase_Connector> m_connector;
    std::shared_ptr<Repository> m_repository;

public:
    explicit Task(std::shared_ptr<Client_Socket> socket,
                  std::shared_ptr<IDatabase_Connector> connector,
                  std::shared_ptr<Repository> repository)
    :m_socket(std::move(socket)),m_connector(std::move(connector)), m_repository(std::move(repository)){}
    Task()=default;
    virtual ~Task() = default;
    virtual void Execute() = 0;
};


#endif //SERVER_TASK_H
