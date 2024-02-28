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
    Task* Create_Task(Client_Socket* socket, IMessage* message, Database_Connector* connector)override{
        return dynamic_cast<Task*>(new Authorization_Task(socket,dynamic_cast<Authorization_Message*>(message),connector));
    }
};

#endif //SERVER_AUTHORIZATION_TASK_CREATOR_H
