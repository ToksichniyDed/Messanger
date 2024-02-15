//
// Created by super on 13.11.2023.
//

#include "Client_Socket_Manager.h"

Client_Socket_Manager::Client_Socket_Manager(SOCKET* socket) : m_socket(socket) {}

void Client_Socket_Manager::Close_Socket() {
    closesocket(*m_socket);
    *m_socket = INVALID_SOCKET;
}

void Client_Socket_Manager::Set_Security_Options() {

}

//Проверка сокета, соединение может быть разорванно некорректно со стороны клиента
bool Client_Socket_Manager::Check_Socket() {
    std::string check_client = Pack_Json("check", "1");
    if (send(*m_socket, check_client.c_str(), check_client.size(), 0) == SOCKET_ERROR)
        return false;
    return true;
}









