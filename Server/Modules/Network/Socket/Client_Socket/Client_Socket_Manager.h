//
// Created by super on 13.11.2023.
//

#ifndef SERVER_CLIENT_SOCKET_MANAGER_H
#define SERVER_CLIENT_SOCKET_MANAGER_H

#include <vector>
#include <iostream>
#include <exception>
#include <memory>

#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET MySocketType;
#else
#include <sys/socket.h>
typedef int MySocketType;
#define closesocket close
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

#include "../ISocket.h"
#include "../../../Tools/Json_Tools.h"

//Реализация менеджера сокета-открытие, закрытие, проверка на существование.

class Client_Socket_Manager : public ISocket {
private:
    std::shared_ptr<MySocketType> m_socket;

public:
    explicit Client_Socket_Manager(std::shared_ptr<MySocketType> socket);
    void Close_Socket() override;
    void Set_Security_Options() override;
    virtual bool Check_Socket();
};


#endif //SERVER_CLIENT_SOCKET_MANAGER_H
