//
// Created by super on 18.11.2023.
//

#include "Task_Factory.h"

Task_Factory::Task_Factory() {
    Register_Task("registration_data", [](Client_Socket* socket, IMessage* message) -> Task*
    { return new Registration_Task(socket, dynamic_cast<Registration_Protocol *>(message)); });
    Register_Task("authorization_data", [](Client_Socket* socket, IMessage* message) -> Task*
    { return new Authorization_Task(socket, dynamic_cast<Authorization_Protocol *>(message)); });
}

//заполнение мапы c помошью метода Register_Task()
void Task_Factory::Register_Task(const std::string &type, Task_Creator creator) {
    Task_Registry[type] = std::move(creator);
}

//Создание задачи. Из параметра type берется строка-тип задачи, ищется по мапе совпадение и создается соответствующая задача.
//Если совпадений нет, то возвращается нулевой указатель
Task* Task_Factory::CreateTask(const std::string &type, Client_Socket* socket,IMessage* message) {
    auto it = Task_Registry.find(type);
    if (it != Task_Registry.end())
        return it->second(socket, message);
    return nullptr;
}
