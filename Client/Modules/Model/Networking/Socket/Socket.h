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
#include "../../../../Message_Factory_Config.h"

class Socket{
public:
    using socket_shared_ptr = std::shared_ptr<boost::asio::ip::tcp::socket>;
    using io_context = std::shared_ptr<boost::asio::io_context>;
    using buffer = std::shared_ptr<boost::asio::streambuf>;
    using instance_socket = std::shared_ptr<Socket>;

protected:
    static instance_socket m_instance;
    io_context m_io_context;
    socket_shared_ptr m_socket;
    buffer m_socket_buffer;

    //std::shared_ptr<Message_To_Server_Queue> m_message_to_server_queue;
    std::shared_ptr<Message_From_Server_Queue> m_message_from_server_queue;
    std::unique_ptr<Socket_Manager> m_socket_manager;
    std::unique_ptr<TFactory<std::string, IMessage>> m_message_factory;

    void Listen_Socket();
    explicit Socket(std::shared_ptr<Message_From_Server_Queue> message_queue = nullptr,
                    std::unique_ptr<Socket_Manager> socket_manager = nullptr,
                    std::unique_ptr<TFactory<std::string, IMessage>> factory = nullptr);
//                    std::shared_ptr<Message_To_Server_Queue> message_to_queue = nullptr);

public:
    static instance_socket Instance(){
        if(!m_instance)
        {
            auto factory = Message_Factory_Config::Message_Factory_Config();
            auto factory_ptr = std::make_unique<TFactory<std::string, IMessage>>(std::move(factory));
            auto temp =  new Socket(Message_From_Server_Queue::Instance(), nullptr, std::move(factory_ptr));
            m_instance = std::shared_ptr<Socket>(temp);
        }
        return m_instance;
    }
    void Socket_Start();
    void Send_Socket(std::shared_ptr<IMessage> message);
};


#endif //CLIENT_SOCKET_H
