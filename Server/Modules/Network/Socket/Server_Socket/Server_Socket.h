//
// Created by super on 13.11.2023.
//

#ifndef SERVER_SERVER_SOCKET_H
#define SERVER_SERVER_SOCKET_H
#define HTONS 8080
#define IP_ADRESS "127.0.0.1"
#define BACKLOG 5

#include <thread>
#include <memory>
#include <boost/di.hpp>

#include "../ISocket.h"
#include "../Client_Socket/Client_Socket.h"
#include "../Client_Manager.h"

//Реализация серверного сокета.Открытие,закрытие, проверка, режим прослушки, прием подключений.

class Server_Socket : public ISocket {
protected:
    bool m_should_exit = false;
    MySocketType m_server_socket = 0;
    std::unique_ptr<Client_Manager> m_client_manager;

    virtual void Bind_Socket();
    virtual void Listening_Socket();
    void Iteration(MySocketType temp_client_socket, sockaddr_in client_address, MySocketLenght client_address_length);

public:
    explicit Server_Socket(std::unique_ptr<Client_Manager> m_client_manager);
    void Open_Socket() override;
    void Close_Socket() override;
    void Set_Security_Options() override;
    virtual void Accept();
    virtual void Listening_Clients_Socket();
};


#endif //SERVER_SERVER_SOCKET_H
