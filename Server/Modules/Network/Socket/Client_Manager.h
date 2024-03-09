//
// Created by super on 15.11.2023.
//

#ifndef SERVER_CLIENT_MANAGER_H
#define SERVER_CLIENT_MANAGER_H

#include <memory>

#include "Client_Socket/Client_Socket.h"
#include "../../Thread/Pool/Task_Container.h"
#include "../../Tools/Containers/Container_Vector.h"
#include "../../Tools/Containers/TContainer_Queue.h"
#include "../../Business_Logic/Task/include/Task_Factory.h"
#include "../../Tools/Json_Tools.h"
#include "Message/include/Message_Factory.h"

//Класс для управления подключенными клиентами. Тут содержиться вектор подключенных клиентов, контейнер задач, и фабрика задач.

class Client_Manager {
protected:
    bool m_should_exit = false;
    std::unique_ptr<Container_Vector<std::shared_ptr<Client_Socket>>> m_connected_clients;
    std::unique_ptr<Task_Container> m_clients_tasks;
    std::unique_ptr<Task_Factory> m_task_factory;
    std::unique_ptr<Message_Factory> m_message_factory;

public:
    explicit Client_Manager(std::unique_ptr<Container_Vector<std::shared_ptr<Client_Socket>>> connected_clients = nullptr,
                   std::unique_ptr<Task_Container> clients_tasks = nullptr,
                   std::unique_ptr<Task_Factory> task_factory = nullptr , std::unique_ptr<Message_Factory> messageFactory = nullptr);
    void Add_New_Client(std::shared_ptr<Client_Socket> clientSocket);
    void Remove_Client(int temp);
    void Listen_Clients();
    void Iteration();
    void Stop_Listening();
};


#endif //SERVER_CLIENT_MANAGER_H
