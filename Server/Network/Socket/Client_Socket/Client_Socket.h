//
// Created by super on 13.11.2023.
//

#ifndef SERVER_CLIENT_SOCKET_H
#define SERVER_CLIENT_SOCKET_H

#include <vector>
#include <winsock2.h>

#include "../ISocket.h"
#include "../Client_Socket/Client_Socket_Manager.h"

class Client_Socket : public ISocket {
protected:
    SOCKET m_socket = 0;
    Client_Socket_Manager m_manager;

public:
    explicit Client_Socket(SOCKET socket);
    void Close_Socket() override;
    void Set_Security_Options() override;
    bool Check_Socket();
    SOCKET& Get_Socket();
    Client_Socket_Manager& Get_Manager();
};


#endif //SERVER_CLIENT_SOCKET_H
