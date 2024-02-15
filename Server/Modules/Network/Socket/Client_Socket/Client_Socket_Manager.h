//
// Created by super on 13.11.2023.
//

#ifndef SERVER_CLIENT_SOCKET_MANAGER_H
#define SERVER_CLIENT_SOCKET_MANAGER_H

#include <vector>
#include <winsock2.h>
#include <iostream>
#include <exception>

#include "../ISocket.h"
#include "../../../Tools/Json_Tools.h"

//Реализация менеджера сокета-открытие, закрытие, проверка на существование.

class Client_Socket_Manager : public ISocket {
private:
    SOCKET* m_socket;

public:
    explicit Client_Socket_Manager(SOCKET* socket);
    void Close_Socket() override;
    void Set_Security_Options() override;
    virtual bool Check_Socket();
};


#endif //SERVER_CLIENT_SOCKET_MANAGER_H
