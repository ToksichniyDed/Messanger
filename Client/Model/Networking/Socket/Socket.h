//
// Created by super on 28.11.2023.
//

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <boost/asio.hpp>
#include <boost/move/unique_ptr.hpp>
#include <iostream>

#include "Socket_Manager.h"
#include "../Message_Queue/Message_From_Server_Queue.h"

class Socket {
private:
    Message_From_Server_Queue m_message_queue;
    boost::asio::io_context m_io_context;
    boost::asio::ip::tcp::socket m_socket;
    boost::movelib::unique_ptr<Socket_Manager> m_socket_manager;
    void Listen_Socket();
    void Send_Socket(std::string& message);

public:
    Socket();
    void Socket_Start();
    Message_From_Server_Queue& Get_Queue();
};


#endif //CLIENT_SOCKET_H
