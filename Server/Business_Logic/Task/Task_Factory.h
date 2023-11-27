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
#include "Task_Type/Registration_Task.h"
#include "Task_Type/Authorization_Task.h"
#include "../../Network/Socket/Client_Socket/Client_Socket_Manager.h"

class Task_Factory {
private:
    using Task_Creator = std::function<Task*(Client_Socket*, std::string&)>;
    std::unordered_map<std::string, Task_Creator> Task_Registry;

public:
    Task_Factory();
    void Register_Task(const std::string& type, Task_Creator creator);
    Task* CreateTask(const std::string& type, Client_Socket* socket , std::string& parse_data);
};

#endif //SERVER_TASK_FACTORY_H
