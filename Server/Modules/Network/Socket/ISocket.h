//
// Created by super on 13.11.2023.
//

#ifndef SERVER_ISOCKET_H
#define SERVER_ISOCKET_H

#include <iostream>
#include <exception>
#include <memory>

#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET MySocketType;
typedef int MySocketLenght;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef int MySocketType;
typedef socklen_t MySocketLenght;
#endif



//Честно говоря, не обязательный класс интерфейс сокетов, но возможно пригодиться

class ISocket {
public:
    virtual void Open_Socket() {};
    virtual void Close_Socket() = 0;
    virtual void Set_Security_Options() {};
    virtual ~ISocket() = default;
};

#endif //SERVER_ISOCKET_H
