//
// Created by super on 28.11.2023.
//

#include "Socket.h"

Socket::Socket():m_socket(m_io_context) {
    auto temp_ptr = new Socket_Manager(&m_socket,&m_io_context);
    m_socket_manager.reset(temp_ptr);
}

void Socket::Listen_Socket() {
    boost::asio::streambuf socket_buffer;
    boost::asio::async_read(m_socket, socket_buffer,
                            [](const boost::system::error_code& error, std::size_t bytes_transferred){
        if (!error) {
            std::cout << "Read " << bytes_transferred << " bytes\n";
        } else {
            std::cerr << "Read error: " << error.message() << "\n";
        }
    });
    std::string message(boost::asio::buffers_begin(socket_buffer.data()), boost::asio::buffers_end(socket_buffer.data()));
    m_message_queue.Add_Message(message);
}

void Socket::Send_Socket(std::string &message) {
    boost::asio::async_write(m_socket, boost::asio::buffer(message), [](const boost::system::error_code& error, std::size_t bytes_transferred){
        if (!error) {
            std::cout << "Wrote " << bytes_transferred << " bytes\n";
        } else {
            std::cerr << "Write error: " << error.message() << "\n";
        }
    });
}

void Socket::Socket_Start() {
    m_socket_manager->Connect();
    Listen_Socket();
    Send_Socket((std::string&)"Привет Сервер!");
}

Message_From_Server_Queue &Socket::Get_Queue() {
    return m_message_queue;
}


