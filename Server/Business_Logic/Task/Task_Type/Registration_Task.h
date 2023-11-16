//
// Created by super on 18.11.2023.
//

#ifndef SERVER_REGISTRATION_TASK_H
#define SERVER_REGISTRATION_TASK_H

#include "../Task.h"
#include "../../../Network/Socket/Client_Socket/Client_Socket.h"
#include "../../Database/Database_Manager.h"
#include "../../../Network/Protocols/Protocols_Type/Registration_Message.h"
#include "../../../Network/Protocols/IMessage_Builder.h"

class Registration_Task: public Task{
private:
    Database_Manager m_manager;
    Client_Socket* m_socket;
    std::string m_data;

public:
    explicit Registration_Task(Client_Socket* socket, std::string& data);
    void Execute() override;
};


#endif //SERVER_REGISTRATION_TASK_H
