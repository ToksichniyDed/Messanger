//
// Created by Toksichniy_Ded on 27.02.2024.
//

#ifndef SERVER_AUTHORIZATION_TASK_CREATOR_H
#define SERVER_AUTHORIZATION_TASK_CREATOR_H

#include "ITask_Creator.h"
#include "../Task_Type/include/Authorization_Task.h"
#include "../../../Network/Socket/Message/include/Authorization_Message.h"

class Authorization_Task_Creator: public ITask_Creator{
public:
    std::unique_ptr<Task> Create_Task(std::shared_ptr<Client_Socket> socket, std::unique_ptr<IMessage> message, std::shared_ptr<IDatabase_Connector> connector)override{

        return std::make_unique<Authorization_Task>(socket,std::move(message),connector, m_repository);
    }
};

#endif //SERVER_AUTHORIZATION_TASK_CREATOR_H
