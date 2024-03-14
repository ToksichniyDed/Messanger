//
// Created by Toksichniy_Ded on 27.02.2024.
//

#ifndef SERVER_ITASK_CREATOR_H
#define SERVER_ITASK_CREATOR_H

#include <memory>

#include "Task.h"
#include "../../Database/Pool/Pool_Connection.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../../Network/Socket/Message/include/IMessage.h"


class ITask_Creator {
public:
//    std::shared_ptr<Client_Socket> socket,
//            std::shared_ptr<IMessage> message,
//    std::shared_ptr<IDatabase_Connector> connector
    virtual std::unique_ptr<Task> Create_Task(std::shared_ptr<Client_Socket> socket,
                                              std::unique_ptr<IMessage> message,
                                              std::shared_ptr<IDatabase_Connector> connector) = 0;
    virtual ~ITask_Creator() = default;
};


#endif //SERVER_ITASK_CREATOR_H
