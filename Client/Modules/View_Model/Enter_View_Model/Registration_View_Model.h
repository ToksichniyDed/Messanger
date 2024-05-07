//
// Created by Toksichniy_Ded on 10.04.2024.
//

#ifndef CLIENT_REGISTRATION_VIEW_MODEL_H
#define CLIENT_REGISTRATION_VIEW_MODEL_H

#include <memory>
#include <utility>

#include "I_View_Model.h"
#include "../../Model/Networking/Message_Queue/Message_To_Server_Queue.h"
#include "../../Model/Networking/Socket/Message_Type/To_Server/Registration_Message_Data.h"
#include "../../View/Enter_View/Register.h"

class Registration_View_Model: public I_View_Model{
public:
    using Register_View_Ptr = std::unique_ptr<Register>;
    using Register_Message_Ptr = std::shared_ptr<Registration_Message_Data>;
    //using Queue_Ptr = std::shared_ptr<Message_To_Server_Queue>;

protected:
    Register_View_Ptr m_register_view;
    Register_Message_Ptr m_register_data;
    //Queue_Ptr m_message_queue;

public:
    explicit Registration_View_Model(Register_View_Ptr register_view, Register_Message_Ptr register_data)://, Queue_Ptr message_queue):
    m_register_view(std::move(register_view)),m_register_data(std::move(register_data)){}//,m_message_queue(std::move(message_queue)){}
    void  Start_Registration(){
        std::string telNumber, password;
        do {
            telNumber = m_register_view->Set_Telephone_Number();
        } while (telNumber.empty());
        do {
            password = m_register_view->Set_Password();
        } while (password.empty());
        m_register_data = std::make_shared<Registration_Message_Data>(telNumber, password);
        m_socket->Send_Socket(m_register_data);
    }
};


#endif //CLIENT_REGISTRATION_VIEW_MODEL_H
