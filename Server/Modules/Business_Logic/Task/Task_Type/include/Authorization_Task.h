//
// Created by super on 18.11.2023.
//

#ifndef SERVER_AUTHORIZATION_TASK_H
#define SERVER_AUTHORIZATION_TASK_H

#include "../../include/Task.h"
#include "../../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../../../Tools/OpenSSL_Tools.h"
#include "../../../Database/Pool/Pool_Connection.h"
#include "../../../../Network/Socket/Message/include/Authorization_Message.h"
#include "../../../../Network/Protocols/Protocols_Type/Authorization_Protocol.h"
#include "../../../Database/Repository.h"


//Задача авторизации
class Authorization_Task: public Task{
public:
    explicit Authorization_Task(Client_Socket* socket, Authorization_Message* message, Database_Connector* connector);
    void Execute() override;
};


#endif //SERVER_AUTHORIZATION_TASK_H
