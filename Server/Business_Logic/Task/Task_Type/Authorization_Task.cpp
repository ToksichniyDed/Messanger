//
// Created by super on 18.11.2023.
//

#include "Authorization_Task.h"

void Authorization_Task::Execute() {
    std::string telephone_number = Unpack_Json("telephone_number", m_data);
    std::string password = Unpack_Json("password", m_data);
    std::cout << "Телефон: " << telephone_number
              << " Номер: " << password << std::endl;

    if(){

    }
    else
    {

    }
}

Authorization_Task::Authorization_Task(Client_Socket* socket, std::string &data): m_socket(socket), m_data(data) {
}
