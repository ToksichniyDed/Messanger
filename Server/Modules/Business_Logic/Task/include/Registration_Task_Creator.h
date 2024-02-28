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
    Task* Create_Task(Client_Socket* socket, IMessage* message, Database_Connector* connector) override{
        return dynamic_cast<Task*>(new Registration_Task(socket,dynamic_cast<Registration_Message*>(message),connector));

    }
};


#endif //SERVER_REGISTRATION_TASK_CREATOR_H
