//
// Created by super on 18.11.2023.
//

#include "include/Task_Factory.h"

Task_Factory::Task_Factory(Pool_Connection* poolConnection):m_pool_connection(poolConnection) {
}

//заполнение мапы c помошью метода Create_Task()
void Task_Factory::Register_Task(const std::string &type, ITask_Creator* creator) {
    auto it = m_task_map.find(type);
    if(it == m_task_map.end())
        m_task_map.insert(std::make_pair(type,creator));
}

//Создание задачи. Из параметра type берется строка-тип задачи, ищется по мапе совпадение и создается соответствующая задача.
//Если совпадений нет, то возвращается нулевой указатель
Task* Task_Factory::Create_Task(const std::string &type, Client_Socket* socket, IMessage* message) {
    auto it = m_task_map.find(type);
    if (it != m_task_map.end()){
        return it->second->Create_Task(socket, message,
                                       /*поменять*/dynamic_cast<Database_Connector*>(m_pool_connection->Take_Connector_From_Queue()));
    }
    return nullptr;
}

