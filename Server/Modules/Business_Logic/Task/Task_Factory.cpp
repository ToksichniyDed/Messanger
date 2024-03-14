//
// Created by super on 18.11.2023.
//
#include "include/Task_Factory.h"

Task_Factory::Task_Factory(std::unique_ptr<Pool_Connection> poolConnection) {
    if(poolConnection)
        m_pool_connection = std::move(poolConnection);
    else
        m_pool_connection = std::make_unique<Pool_Connection>();
}

//заполнение мапы c помошью метода Create_Task()
void Task_Factory::Register_Task(const std::string &type, std::unique_ptr<ITask_Creator> creator) {
    auto it = m_task_map.find(type);
    if(it == m_task_map.end())
        m_task_map.insert(std::make_pair(type,std::move(creator)));
}

//Создание задачи. Из параметра type берется строка-тип задачи, ищется по мапе совпадение и создается соответствующая задача.
//Если совпадений нет, то возвращается нулевой указатель
std::unique_ptr<Task> Task_Factory::Create_Task(const std::string &type, std::shared_ptr<Client_Socket> socket, std::unique_ptr<IMessage> message) {
    auto it = m_task_map.find(type);
    if (it != m_task_map.end()){
        return std::move(it->second->Create_Task(std::move(socket), std::move(message),m_pool_connection->Take_Connector_From_Pool()));
    }
    return nullptr;
}

