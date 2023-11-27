//
// Created by super on 13.11.2023.
//

#ifndef SERVER_SERVER_SOCKET_H
#define SERVER_SERVER_SOCKET_H

#include "../ISocket.h"
#include "../Client_Socket/Client_Socket.h"
#include "../Client_Manager.h"

class Server_Socket : public ISocket {
private:
    SOCKET m_server_socket = 0;
    Client_Manager m_client_manager;
    void Bind_Socket();
    void Listening_Socket();

public:
    void Open_Socket() override;
    void Close_Socket() override;
    void Set_Security_Options() override;
    void Accept();
};


#endif //SERVER_SERVER_SOCKET_H
