//
// Created by Toksichniy_Ded on 27.02.2024.
//

#ifndef SERVER_REGISTRATION_TASK_CREATOR_H
#define SERVER_REGISTRATION_TASK_CREATOR_H

#include "ITask_Creator.h"
#include "../Task_Type/include/Registration_Task.h"
#include "../../../Network/Socket/Message/include/Registration_Message.h"

class Registration_Task_Creator: public ITask_Creator {
public:
    std::unique_ptr<Task> Create_Task(std::shared_ptr<Client_Socket> socket, std::shared_ptr<IMessage> message, std::shared_ptr<IDatabase_Connector> connector)override{
        return std::move(std::make_unique<Registration_Task>(socket,message,connector));
    }
};


#endif //SERVER_REGISTRATION_TASK_CREATOR_H
