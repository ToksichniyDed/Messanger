//
// Created by super on 28.11.2023.
//

#include "Socket_Manager.h"

Socket_Manager::Socket_Manager(boost::asio::ip::tcp::socket *socket, boost::asio::io_context* io_context):m_socket_to_manage(socket),m_io_context_to_manage(io_context) {
}

void Socket_Manager::Close_Socket() {
    m_socket_to_manage->close();
}

void Socket_Manager::Connect() {
    m_endpoint = boost::asio::ip::tcp::endpoint (boost::asio::ip::address::from_string(IP_ADRESS), PORT);
    m_socket_to_manage->connect(m_endpoint);
    if(Is_Connected())
        std::cout<<"Success connection!"<<std::endl;
    else
        std::cout<<"Unsuccess connection!"<<std::endl;
}

bool Socket_Manager::Is_Connected() {
    return m_socket_to_manage->is_open();
}

