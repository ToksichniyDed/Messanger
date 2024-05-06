//
// Created by super on 18.11.2023.
//

#include <utility>

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

Registration_Task::Registration_Task(std::shared_ptr<Client_Socket> socket,
                                     std::unique_ptr<IMessage> message,
                                     std::shared_ptr<IDatabase_Connector> connector,
                                     std::shared_ptr<Repository> repository){
    if(socket)
        m_socket = std::move(socket);

    if(message){
        auto* temp = dynamic_cast<Registration_Message*>(message.release());
        if(temp)
            m_message = std::make_unique<Registration_Message>(*temp);
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

