//
// Created by super on 18.11.2023.
//

#include "include/Authorization_Task.h"

//Распаковка отправленных данных. Для проверки авторизации сначала создается запрос в бд по номеру телефона клиента.
//Если номер существует, то вытаскивается соль и хэш пароля. Далее с помощью OpenSSl_Tools хэшируется распакованный пароль + соль,
//и сравнивается с полученным из бд хэш-паролем.
//В зависимости от результата сравнения создается ответное сообщение с помощью билдера сообщений.
void Authorization_Task::Execute() {
    try {
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;

        IMessage_Builder *message_builder = new Authorization_Protocol();
        std::string access = "error";
        std::string message = message_builder->Set_Content(access).Set_Parametrs().Build_Message();
        m_socket->Send_Message(message);
    }
}

Authorization_Task::Authorization_Task(Client_Socket *socket, Authorization_Protocol* message) :
        m_socket(socket), m_message(message){
}
