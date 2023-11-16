//
// Created by super on 13.11.2023.
//

#include <iostream>
#include <exception>

#include "Client_Socket.h"
#include "../../../Tools/Json_Tools.h"

Client_Socket::Client_Socket(SOCKET socket) : m_socket(socket) {}

void Client_Socket::Close_Socket() {
    closesocket(m_socket);
}

void Client_Socket::Set_Security_Options() {

}

bool Client_Socket::Check_Socket() {
    std::string check_client = Pack_Json("check", "1");
    if (send(m_socket, check_client.c_str(), check_client.size(), 0) == SOCKET_ERROR)
        return false;
    return true;
}

SOCKET& Client_Socket::Get_Socket() {
    return m_socket;
}

Client_Socket_Manager &Client_Socket::Get_Manager() {
    return m_manager;
}





