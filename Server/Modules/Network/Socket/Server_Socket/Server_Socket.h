//
// Created by super on 13.11.2023.
//

#ifndef SERVER_SERVER_SOCKET_H
#define SERVER_SERVER_SOCKET_H
#define HTONS 8080
#define IP_ADRESS "127.0.0.1"
#define BACKLOG 5

#include <thread>

#include "../ISocket.h"
#include "../Client_Socket/Client_Socket.h"
#include "../Client_Manager.h"

//Реализация серверного сокета.Открытие,закрытие, проверка, режим прослушки, прием подключений.

class Server_Socket : public ISocket {
protected:
    bool m_should_exit = false;
    SOCKET m_server_socket = 0;
    Client_Manager* m_client_manager;
    virtual void Bind_Socket();
    virtual void Listening_Socket();

public:
    Server_Socket(Client_Manager* m_client_manager);
    void Open_Socket() override;
    void Close_Socket() override;
    void Set_Security_Options() override;
    virtual void Accept();
    virtual void Listening_Clients_Socket();
    void Iteration(SOCKET temp_client_socket, sockaddr_in client_address, int client_address_length);
};


#endif //SERVER_SERVER_SOCKET_H