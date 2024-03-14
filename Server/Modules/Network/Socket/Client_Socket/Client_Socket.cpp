//
// Created by super on 23.11.2023.
//

#include "Client_Socket.h"


//Прослушивание сокета на предмет новых сообщений. Если сообщение есть,
//то создаеться пара Сокет*-сообщение, которая и возвращается, в дальнешем используется в Client_Manager.
std::pair<Client_Socket*, std::vector<char>> Client_Socket::Listen_Socket() {
    std::cout << "Socket " << m_socket << " have message!" << std::endl;
    try {
        std::vector<char> client_buffer(1024);

        int received_bytes = recv(m_socket, client_buffer.data(), 1024, 0);
        if (received_bytes <= 0)
            throw std::runtime_error("No message to read!");

        std::pair<Client_Socket* , std::vector<char>> ans = std::make_pair(this, client_buffer);
        return ans;
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return std::make_pair(this, std::vector<char>());
    }
}

//Отправка сообщения по сокету
void Client_Socket::Send_Message(/*std::move()*/ std::string message) {
    try {
        if(!send(m_socket, message.c_str(), message.length(), 0))
            throw std::runtime_error("Failed send message!");
    }
    catch (std::exception& Error)
    {
        std::cout<<"Error: "<<Error.what()<<std::endl;
    }
}

Client_Socket::Client_Socket(std::shared_ptr<Client_Socket_Manager> manager, SOCKET socket):m_socket(socket) {
    if(manager)
        m_socket_manager = std::move(manager);
    else
        m_socket_manager = std::make_shared<Client_Socket_Manager>(&socket);
}

std::shared_ptr<Client_Socket_Manager> Client_Socket::Get_Client_Socket_Manager() {
    return m_socket_manager;
}

SOCKET Client_Socket::Get_Socket() const {
    return m_socket;
}







