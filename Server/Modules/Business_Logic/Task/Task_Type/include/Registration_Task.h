//
// Created by super on 18.11.2023.
//

#ifndef SERVER_REGISTRATION_TASK_H
#define SERVER_REGISTRATION_TASK_H

#include "../../Task.h"
#include "../../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../../Database/Pool/Database_Connector.h"
#include "../../../../Network/Protocols/Protocols_Type/Registration_Protocol.h"
#include "../../../../Network/Protocols/IMessage_Builder.h"
#include "../../../../Tools/OpenSSL_Tools.h"
#include "../../../../Network/Socket/Message/include/Registration_Message.h"


//Задача регистрации

class Registration_Task: public Task{
private:
    Client_Socket* m_socket;
    Registration_Protocol* m_message;

public:
    explicit Registration_Task(Client_Socket* socket, Registration_Protocol* message);
    void Execute() override;
};


#endif //SERVER_REGISTRATION_TASK_H
