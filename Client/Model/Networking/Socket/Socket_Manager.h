//
// Created by super on 28.11.2023.
//

#ifndef CLIENT_SOCKET_MANAGER_H
#define CLIENT_SOCKET_MANAGER_H
#define IP_ADRESS "127.0.0.1"
#define PORT 8080

#include <boost/asio.hpp>
#include <iostream>

class Socket_Manager {
private:
    boost::asio::ip::tcp::socket* m_socket_to_manage;
    boost::asio::io_context* m_io_context_to_manage;
    boost::asio::ip::tcp::endpoint m_endpoint;

public:
    Socket_Manager(boost::asio::ip::tcp::socket* socket, boost::asio::io_context* io_context);
    void Connect();
    void Close_Socket();
    bool Is_Connected();
};


#endif //CLIENT_SOCKET_MANAGER_H
