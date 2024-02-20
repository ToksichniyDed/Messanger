//
// Created by super on 18.11.2023.
//

#include "Registration_Task.h"

//Распаковка оправленных данных. С помощью OpenSSL_Tools пароль+соль хэшируется, после чего создается запрос
// (с помощью класса Query_Executor) в базу данных на добавление нового пользователя.
// В базу добавляется номер телефона, соль и  хэшированный пароль. В соответствии с результатом создается ответное сообщение с помощью билдера.
//Так как строка хэшируется, то можно не опасаться SQL-инъекции.
void Registration_Task::Execute() {
    try {

    }catch (std::exception& Error){
        std::cout<<"Error: "<<Error.what()<<std::endl;
    }
}

Registration_Task::Registration_Task(Client_Socket* socket, std::string &data):
m_socket(socket), m_data(data) {

}
