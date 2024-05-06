//
// Created by Toksichniy_Ded on 27.02.2024.
//

#ifndef SERVER_ITASK_CREATOR_H
#define SERVER_ITASK_CREATOR_H

#include <memory>
#include <boost/di.hpp>

#include "Task.h"
#include "../../Database/Pool/Pool_Connection.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../../Network/Socket/Message/include/IMessage.h"


class ITask_Creator {
protected:
    std::shared_ptr<Repository> m_repository;

public:
//    std::shared_ptr<Client_Socket> socket,
//            std::shared_ptr<IMessage> message,
//    std::shared_ptr<IDatabase_Connector> connector
    ITask_Creator();
    virtual std::unique_ptr<Task> Create_Task(std::shared_ptr<Client_Socket> socket,
                                              std::unique_ptr<IMessage> message,
                                              std::shared_ptr<IDatabase_Connector> connector) = 0;
    virtual ~ITask_Creator() = default;
};

inline ITask_Creator::ITask_Creator() {
    auto inj = boost::di::make_injector(
            boost::di::bind<User_Handler>.to([] { return std::make_unique<User_Handler>(); }),
            boost::di::bind<Password_Handler>.to([] { return std::make_unique<Password_Handler>(); })
            );
    m_repository = inj.create<std::shared_ptr<Repository>>();
}


#endif //SERVER_ITASK_CREATOR_H
