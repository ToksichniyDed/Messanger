//
// Created by super on 18.11.2023.
//

#ifndef SERVER_TASK_FACTORY_H
#define SERVER_TASK_FACTORY_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>

#include "Task.h"
#include "ITask_Creator.h"
#include "../Task_Type/include/Task_Headers.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket_Manager.h"
#include "../../Database/Pool/Pool_Connection.h"
#include "../../Database/Pool/Database_Connector.h"
#include "../../../Network/Socket/Message/include/Message_Headers.h"

//Паттер Factory для формирования задач.
class Task_Factory{
public:
    using Task_Map = std::unordered_map<std::string, ITask_Creator*> ;

protected:
    std::unique_ptr<Pool_Connection> m_pool_connection;
    Task_Map m_task_map;

public:
    explicit Task_Factory(std::unique_ptr<Pool_Connection> = nullptr);
    virtual ~Task_Factory() = default;
    void Register_Task(const std::string& type, ITask_Creator* creator);
    virtual std::unique_ptr<Task> Create_Task(const std::string &type, std::shared_ptr<Client_Socket> socket, std::unique_ptr<IMessage> message);
};

#endif //SERVER_TASK_FACTORY_H
