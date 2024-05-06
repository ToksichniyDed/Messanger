//
// Created by super on 13.11.2023.
//

#include "Client_Socket_Manager.h"

#include <utility>

Client_Socket_Manager::Client_Socket_Manager(std::shared_ptr<MySocketType> socket) : m_socket(std::move(socket)) {}

void Client_Socket_Manager::Close_Socket() {
    closesocket(*m_socket);
    *m_socket = INVALID_SOCKET;
}

void Client_Socket_Manager::Set_Security_Options() {

}

//Проверка сокета, соединение может быть разорванно некорректно со стороны клиента
bool Client_Socket_Manager::Check_Socket() {
    char client_buffer[1];
#ifdef WIN32
    u_long nonBlockingMode = 1;
    if (ioctlsocket(*m_socket, FIONBIO, &nonBlockingMode) != 0) {
        throw std::runtime_error("Failed to set socket to non-blocking mode.");
    }
#else
    int flags = fcntl(*m_socket, F_GETFL, 0);
        if (flags == -1) {
        throw std::runtime_error("Failed to get socket flags.");
        }

        // Установка неблокирующего режима для сокета
        if (fcntl(*m_socket, F_SETFL, flags | O_NONBLOCK) == -1) {
            throw std::runtime_error("Failed to set socket to non-blocking mode.");
        }
#endif

    int received_bytes = recv(*m_socket, client_buffer, sizeof(client_buffer), MSG_PEEK);
    if (received_bytes == SOCKET_ERROR) {
        if(WSAGetLastError() != WSAEWOULDBLOCK)
            return false;
    }
    return true;
}









