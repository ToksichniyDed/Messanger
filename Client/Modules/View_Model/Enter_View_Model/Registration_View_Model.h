//
// Created by Toksichniy_Ded on 10.04.2024.
//

#ifndef CLIENT_REGISTRATION_VIEW_MODEL_H
#define CLIENT_REGISTRATION_VIEW_MODEL_H

#include <memory>

#include "../../Model/Networking/Message_Queue/Message_To_Server_Queue.h"
#include "../../Model/Networking/Socket/Message_Type/To_Server/Registration_Message_Data.h"
#include "../../View/Enter_View/Register.h"

class Registration_View_Model {
protected:
    std::unique_ptr<Register> m_register_view;
    std::shared_ptr<Registration_Message_Data> m_register_data;
    std::shared_ptr<Message_To_Server_Queue> m_message_queue;

public:
    void  Start_Registration(){
        std::string telNumber, password;
        do {
            telNumber = m_register_view->Set_Telephone_Number();
        } while (telNumber.empty());
        do {
            password = m_register_view->Set_Password();
        } while (password.empty());
        m_register_data = std::make_shared<Registration_Message_Data>(telNumber, password);
        m_message_queue->Push_Message(m_register_data);
    }
};


#endif //CLIENT_REGISTRATION_VIEW_MODEL_H
