//
// Created by super on 15.11.2023.
//

#ifndef SERVER_CLIENT_MANAGER_H
#define SERVER_CLIENT_MANAGER_H

#include "Client_Socket/Client_Socket.h"
#include "../../Thread/Pool/Task_Container.h"
#include "../../Tools/Containers/Container_Vector.h"
#include "../../Tools/Containers/TContainer_Queue.h"
#include "../../Business_Logic/Task/Task_Factory.h"
#include "../../Tools/Json_Tools.h"

//Класс для управления подключенными клиентами. Тут содержиться вектор подключенных клиентов, контейнер задач, и фабрика задач.

class Client_Manager {
private:
    Container_Vector<Client_Socket*> m_connected_clients;
    Task_Container m_clients_tasks;
    Task_Factory task_factory;

public:
    void Add_New_Client(Client_Socket *clientSocket);
    void Remove_Client(int temp);
    void Listen_Clients();
};


#endif //SERVER_CLIENT_MANAGER_H
