//
// Created by super on 28.11.2023.
//

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <memory>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/di.hpp>

#include "Socket_Manager.h"
#include "../Message_Queue/Message_From_Server_Queue.h"
#include "../../../Tools/TFactory.h"
#include "../../../Tools/Json_Tools.h"

class Socket{
public:
    using socket_shared_ptr = std::shared_ptr<boost::asio::ip::tcp::socket>;
    using io_context = std::shared_ptr<boost::asio::io_context>;

private:
    io_context m_io_context;
    socket_shared_ptr m_socket;

    std::shared_ptr<Message_From_Server_Queue> m_message_queue;
    std::unique_ptr<Socket_Manager> m_socket_manager;
    TFactory<std::string, IMessage> m_message_factory;


    void Listen_Socket();
    void Send_Socket(std::string message);

public:
    explicit Socket(std::shared_ptr<Message_From_Server_Queue> message_queue = nullptr, std::unique_ptr<Socket_Manager> socket_manager = nullptr);
    void Socket_Start();
};


#endif //CLIENT_SOCKET_H
