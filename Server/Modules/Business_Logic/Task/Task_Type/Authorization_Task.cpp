//
// Created by super on 18.11.2023.
//

#include <utility>

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

Authorization_Task::Authorization_Task(std::shared_ptr<Client_Socket> socket,
                                       std::unique_ptr<IMessage> message,
                                       std::shared_ptr<IDatabase_Connector> connector,
                                       std::shared_ptr<Repository> repository){
    if(socket)
        m_socket = std::move(socket);

    if(message){
        auto* temp = dynamic_cast<Authorization_Message*>(message.release());
        if(temp)
            m_message = std::make_unique<Authorization_Message>(*temp);
        else
            throw std::runtime_error("Pure message");
    }

    if(connector)
        m_connector = std::move(connector);

    if(repository)
        m_repository = std::move(repository);

    if(!(m_socket && m_message && m_connector && m_repository))
        throw std::runtime_error("Failed create Registration_Task!");
}
