//
// Created by super on 28.11.2023.
//

#ifndef CLIENT_SOCKET_MANAGER_H
#define CLIENT_SOCKET_MANAGER_H
#define IP_ADRESS "127.0.0.1"
#define PORT 8080

#include <memory>

#include <boost/asio.hpp>
#include <iostream>

class Socket_Manager {
public:
    using socket_shared_ptr = std::shared_ptr<boost::asio::ip::tcp::socket>;
    using io_context = std::shared_ptr<boost::asio::io_context>;

private:
    socket_shared_ptr m_socket_to_manage;
    io_context m_io_context_to_manage;
    boost::asio::ip::tcp::endpoint m_endpoint;

public:
    explicit Socket_Manager(socket_shared_ptr socket = nullptr, io_context io_context = nullptr);
    void Connect();
    void Close_Socket();
    bool Is_Connected();
};


#endif //CLIENT_SOCKET_MANAGER_H
