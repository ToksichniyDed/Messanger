//
// Created by super on 18.11.2023.
//

#include "include/Authorization_Task.h"

//Задача авторизации. Сначала данные подготавливаются в виде сущностей, далее вызов метода авторизации из репозитория, возвращает
// true/false(успешная авторизация/неуспешная), и отправляется соответсвующее сообщение
void Authorization_Task::Execute() {
    try {
        m_message->Prepare_Data();

    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;

        IMessage_Builder *message_builder = new Authorization_Protocol();
        std::string access = "error";
        std::string message = message_builder->Set_Content(access).Set_Parametrs().Build_Message();
        m_socket->Send_Message(message);
    }
}

Authorization_Task::Authorization_Task(Client_Socket *socket, Authorization_Message* message, Database_Connector* connector):
        Task(socket,dynamic_cast<IMessage*>(message),connector){
}
