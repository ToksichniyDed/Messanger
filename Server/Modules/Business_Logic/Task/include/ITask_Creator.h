//
// Created by Toksichniy_Ded on 27.02.2024.
//

#ifndef SERVER_ITASK_CREATOR_H
#define SERVER_ITASK_CREATOR_H

#include "Task.h"
#include "../../Database/Pool/Pool_Connection.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../../Network/Socket/Message/include/IMessage.h"


class ITask_Creator {
public:
    //Client_Socket* socket, IMessage* message, Database_Connector* connector
    virtual Task* Create_Task(Client_Socket* socket, IMessage* message, Database_Connector* connector) = 0;
};


#endif //SERVER_ITASK_CREATOR_H
