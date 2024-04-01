//
// Created by super on 28.11.2023.
//

#include "Socket.h"

Socket::Socket(std::shared_ptr<Message_From_Server_Queue> message_queue, std::unique_ptr<Socket_Manager> socket_manager){
    m_io_context = std::make_shared<boost::asio::io_context>();
    m_socket = std::make_shared<boost::asio::ip::tcp::socket>(*m_io_context);

    if(socket_manager)
        m_socket_manager = std::move(socket_manager);
    else
        m_socket_manager = std::make_unique<Socket_Manager>(m_socket,m_io_context);

    if(message_queue)
        m_message_queue = std::move(message_queue);
    else{
        auto injector = boost::di::make_injector();
        m_message_queue = injector.create<std::shared_ptr<Message_From_Server_Queue>>();
    }
}

void Socket::Listen_Socket() {
    boost::asio::streambuf socket_buffer;
    boost::asio::async_read(*m_socket, socket_buffer,
                            [](const boost::system::error_code& error, std::size_t bytes_transferred){
        if (!error) {
            std::cout << "Read " << bytes_transferred << " bytes\n";
        } else {
            std::cerr << "Read error: " << error.message() << "\n";
        }
    });
    std::string message(boost::asio::buffers_begin(socket_buffer.data()), boost::asio::buffers_end(socket_buffer.data()));

    try{
        auto temp_message = m_message_factory.Create(Unpack_Json("type",message));
        m_message_queue->Push_Message(std::move(temp_message));
    }
    catch (std::exception& Error){
        std::cout<<Error.what();
    }
}

void Socket::Send_Socket(std::string message) {
    boost::asio::async_write(*m_socket, boost::asio::buffer(message), [](const boost::system::error_code& error, std::size_t bytes_transferred){
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
    Send_Socket("Привет Сервер!");
}



