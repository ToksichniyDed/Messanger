//
// Created by super on 18.11.2023.
//

#ifndef SERVER_AUTHORIZATION_TASK_H
#define SERVER_AUTHORIZATION_TASK_H

#include "../Task.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../../Network/Protocols/Protocols_Type/Authorization_Message.h"
#include "../../../Network/Protocols/IMessage_Builder.h"
#include "../../../Tools/OpenSSL_Tools.h"
#include "../../Database/Pool/Database_Connector.h"

//Задача авторизации

class Authorization_Task: public Task{
private:
    Client_Socket* m_socket;
    std::string m_data;

public:
    explicit Authorization_Task(Client_Socket* socket, std::string& data);
    void Execute() override;
};


#endif //SERVER_AUTHORIZATION_TASK_H
