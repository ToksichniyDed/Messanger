//
// Created by super on 18.11.2023.
//

#include "Authorization_Task.h"

//Распаковка отправленных данных. Для проверки авторизации сначала создается запрос в бд по номеру телефона клиента.
//Если номер существует, то вытаскивается соль и хэш пароля. Далее с помощью OpenSSl_Tools хэшируется распакованный пароль + соль,
//и сравнивается с полученным из бд хэш-паролем.
//В зависимости от результата сравнения создается ответное сообщение с помощью билдера сообщений.

void Authorization_Task::Execute() {
    try {
        std::string telephone_number = Unpack_Json("telephone_number", m_data);
        std::string password = Unpack_Json("password", m_data);
        std::string select_part = "user_id, password, salt";
        std::string where_part = "telephone_number = 'telephone_number'";
        std::string user = "User";
        std::cout << "Телефон: " << telephone_number
                  << " Номер: " << password << std::endl;

        std::vector<std::map<std::string, std::string >> result_vector = m_manager->ExecuteCustomSelect(
                user, select_part, where_part);
        if (!result_vector.empty()) {
            for (auto &temp: result_vector) {
                auto it = temp.find("salt");
                std::string salt = it->second;
                std::string check_password = Create_Hash_With_Salt(password, salt);
                std::string access = "false";

                IMessage_Builder *message_builder = new Authorization_Message();
                select_part = "user_id, username";
                where_part = "telephone_number = 'telephone_number' AND password = 'check_password'";
                if (!m_manager->ExecuteCustomSelect(user, select_part, where_part).empty()) {
                    access = "true";
                    std::string message = message_builder->Set_Content(access).Set_Parametrs().Build_Message();
                    m_socket->Send_Message(message);
                } else {
                    std::string message = message_builder->Set_Content(access).Set_Parametrs().Build_Message();
                    m_socket->Send_Message(message);
                }
                delete message_builder;
            }
        }
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;

        IMessage_Builder *message_builder = new Authorization_Message();
        std::string access = "error";
        std::string message = message_builder->Set_Content(access).Set_Parametrs().Build_Message();
        m_socket->Send_Message(message);
    }
}

Authorization_Task::Authorization_Task(Client_Socket *socket, std::string &data, Database_Manager *manager) :
        m_socket(socket), m_data(data), m_manager(manager) {
}
