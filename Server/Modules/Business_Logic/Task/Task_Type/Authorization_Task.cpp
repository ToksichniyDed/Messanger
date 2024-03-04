//
// Created by super on 18.11.2023.
//

#include "include/Authorization_Task.h"

//Задача авторизации. Сначала данные подготавливаются в виде сущностей, далее вызов метода авторизации из репозитория, возвращает
// true/false(успешная авторизация/неуспешная), и отправляется соответсвующее сообщение
void Authorization_Task::Execute() {
    Authorization_Protocol status_message;
    status_message.Set_Parametrs();
    try {
        m_message->Prepare_Data();
        std::string message;
        if(m_repository->User_Authorization(m_connector, m_message->Get_User(),m_message->Get_Password()))
            message = status_message.Set_Content("true").Build_Message();
        else
            message = status_message.Set_Content("false").Build_Message();

        m_socket->Send_Message(std::move(message));
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;

        std::string message = status_message.Set_Content("error").Build_Message();
        m_socket->Send_Message(std::move(message));
    }
}

Authorization_Task::Authorization_Task(Client_Socket *socket, Authorization_Message* message, Database_Connector* connector, Repository* repository):
        Task(socket,connector,repository), m_message(message){
}
