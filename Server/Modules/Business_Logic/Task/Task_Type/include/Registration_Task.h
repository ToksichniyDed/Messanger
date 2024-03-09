//
// Created by super on 18.11.2023.
//

#ifndef SERVER_REGISTRATION_TASK_H
#define SERVER_REGISTRATION_TASK_H

#include <memory>

#include "../../include/Task.h"
#include "../../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../../Database/Pool/Database_Connector.h"
#include "../../../../Network/Protocols/Protocols_Type/Registration_Protocol.h"
#include "../../../../Network/Protocols/IMessage_Builder.h"
#include "../../../../Network/Socket/Message/include/Registration_Message.h"

//Задача регистрации
class Registration_Task: public Task{
protected:
    std::unique_ptr<Registration_Message> m_message;

public:
    explicit Registration_Task(std::shared_ptr<Client_Socket> socket,
                               std::unique_ptr<IMessage> message,
                               std::shared_ptr<IDatabase_Connector> connector,
                               std::shared_ptr<Repository> repository);
    void Execute() override;
};



#endif //SERVER_REGISTRATION_TASK_H
