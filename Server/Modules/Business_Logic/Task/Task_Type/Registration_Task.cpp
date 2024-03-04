//
// Created by super on 18.11.2023.
//

#include "include/Registration_Task.h"

//Распаковка оправленных данных. С помощью OpenSSL_Tools пароль+соль хэшируется, после чего создается запрос
// (с помощью класса Query_Executor) в базу данных на добавление нового пользователя.
// В базу добавляется номер телефона, соль и  хэшированный пароль. В соответствии с результатом создается ответное сообщение с помощью билдера.
void Registration_Task::Execute() {
    Registration_Protocol status_message;
    status_message.Set_Parametrs();

    try {
        m_message->Prepare_Data();

        std::string message;
        if(m_repository->User_Registration(m_connector,m_message->Get_User(),m_message->Get_Password()))
            message = status_message.Set_Content("true").Build_Message();
        else
            message = status_message.Set_Content("false").Build_Message();

        m_socket->Send_Message(message);
    }catch (std::exception& Error){
        std::cout<<"Error: "<<Error.what()<<std::endl;
        std::string message = status_message.Set_Content("error").Build_Message();
        m_socket->Send_Message(std::move(message));
    }
}

Registration_Task::Registration_Task(Client_Socket *socket, Registration_Message *message, Database_Connector* connector, Repository* repository):
Task(socket, connector, repository), m_message(message){
}

