//
// Created by super on 23.11.2023.
//

#include "Client_Socket.h"

//Прослушивание сокета на предмет новых сообщений. Если сообщение есть,
//то создаеться пара Сокет*-сообщение, которая и возвращается, в дальнешем используется в Client_Manager.
std::pair<std::shared_ptr<Client_Socket>, std::vector<char>> Client_Socket::Listen_Socket() {
    try {
        std::vector<char> client_buffer(1024);

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

        int received_bytes = recv(*m_socket, client_buffer.data(), 1024, 0);
        if (received_bytes <= 0)
            throw std::runtime_error("No message to read!");
        std::cout << "Socket " << *m_socket << " have message!" << std::endl;

        std::pair<std::shared_ptr<Client_Socket>, std::vector<char>> ans = std::make_pair(
                std::make_shared<Client_Socket>(*this), client_buffer);
        return ans;
    } catch (std::exception &Error) {
        //std::cout << "Error: " << Error.what() << std::endl;
        return std::make_pair(std::make_shared<Client_Socket>(*this), std::vector<char>());
    }
}

//Отправка сообщения по сокету
void Client_Socket::Send_Message(/*std::move()*/ std::string message) {
    try {
        if (!send(*m_socket, message.c_str(), static_cast<int>(message.size()), 0))
            throw std::runtime_error("Failed send message!");
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
    }
}

Client_Socket::Client_Socket(std::shared_ptr<Client_Socket_Manager> manager, std::shared_ptr<MySocketType> socket){
    if (manager)
        m_socket_manager = std::move(manager);

    if(socket)
        m_socket = std::move(socket);

    if(!(m_socket_manager && m_socket))
        throw std::runtime_error("Failed create Client_Socket!");
}

std::shared_ptr<Client_Socket_Manager> Client_Socket::Get_Client_Socket_Manager() {
    return m_socket_manager;
}

std::shared_ptr<MySocketType> Client_Socket::Get_Socket() const {
    return m_socket;
}







