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
#include "../../../Network/Socket/Message/include/Message_Headers.h"

//Паттер Factory для формирования задач.
class Task_Factory{
public:
    using Task_Map = std::unordered_map<std::string, ITask_Creator*> ;

protected:
    Pool_Connection* m_pool_connection;
    Task_Map m_task_map;

public:
    explicit Task_Factory(Pool_Connection* poolConnection = nullptr);
    void Register_Task(const std::string& type, ITask_Creator* creator);
    virtual Task* Create_Task(const std::string& type, Client_Socket* socket , IMessage* message);
};

#endif //SERVER_TASK_FACTORY_H
