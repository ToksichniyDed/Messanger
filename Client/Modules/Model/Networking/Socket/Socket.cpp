//
// Created by super on 28.11.2023.
//

#include "Socket.h"

Socket::instance_socket Socket::m_instance = nullptr;

Socket::Socket(std::shared_ptr<Message_From_Server_Queue> message_queue,
               std::unique_ptr<Socket_Manager> socket_manager,
               std::unique_ptr<TFactory<std::string, IMessage>> factory){
//               std::shared_ptr<Message_To_Server_Queue> message_to_queue) {
    m_io_context = std::make_shared<boost::asio::io_context>();
    m_socket = std::make_shared<boost::asio::ip::tcp::socket>(*m_io_context);
    m_socket_buffer = std::make_shared<boost::asio::streambuf>();

        if (socket_manager)
        m_socket_manager = std::move(socket_manager);
        else
        m_socket_manager = std::make_unique<Socket_Manager>(m_socket, m_io_context);

    if (message_queue)
        m_message_from_server_queue = std::move(message_queue);
    else {
        auto injector = boost::di::make_injector(
                boost::di::bind<Message_From_Server_Queue>.to([] { return Message_From_Server_Queue::Instance(); })
        );
        m_message_from_server_queue = injector.create<std::shared_ptr<Message_From_Server_Queue>>();
    }

//    if (message_to_queue)
//        m_message_to_server_queue = std::move(message_to_queue);
//    else {
//        auto injector = boost::di::make_injector(
//                boost::di::bind<Message_To_Server_Queue>.to([] { return Message_To_Server_Queue::Instance(); })
//        );
//        m_message_to_server_queue = injector.create<std::shared_ptr<Message_To_Server_Queue>>();
//    }

    if (factory)
        m_message_factory = std::move(factory);
    else {
        m_message_factory = std::make_unique<TFactory<std::string, IMessage>>(
                Message_Factory_Config::Message_Factory_Config());
    }
}

void Socket::Listen_Socket() {
    boost::asio::async_read(*m_socket, *m_socket_buffer,
                            [&](const boost::system::error_code &error, std::size_t bytes_transferred) {
                                if (!error) {
                                    std::string message(boost::asio::buffers_begin(m_socket_buffer->data()),
                                                        boost::asio::buffers_end(m_socket_buffer->data()));
                                    m_socket_buffer->consume(bytes_transferred);
                                    try {
                                        if (!message.empty()) {
                                            auto temp_message = m_message_factory->Create(Unpack_Json("type", message));
                                            m_message_from_server_queue->Push_Message(std::move(temp_message));
                                        }
                                    }
                                    catch (std::exception &Error) {
                                        std::cout << Error.what();
                                    }
                                    std::cout << "Read " << bytes_transferred << " bytes\n";
                                    Listen_Socket();
                                } else {
                                    //std::cerr << "Read error: " << error.message() << "\n";
                                    Listen_Socket();
                                }
                            });
}

void Socket::Send_Socket(std::shared_ptr<IMessage> message) {
        message->Prepare_Data();
        boost::asio::async_write(*m_socket, boost::asio::buffer(message->Get_Prepared_Data()),
                                 [&](const boost::system::error_code &error, std::size_t bytes_transferred) {
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
    //Send_Socket();
    // Создаем executor для io_context
    boost::asio::executor executor = m_io_context->get_executor();
    // Запускаем цикл обработки событий в отдельном потоке
    boost::asio::post(executor, [&]() {m_io_context->run();});
}



