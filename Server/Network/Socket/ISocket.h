//
// Created by super on 13.11.2023.
//

#ifndef SERVER_ISOCKET_H
#define SERVER_ISOCKET_H

#include <iostream>
#include <exception>
#include <winsock2.h>
#include <memory>

//Честно говоря, не обязательный класс интерфейс сокетов, но возможно пригодиться

class ISocket {
public:
    virtual void Open_Socket() {};
    virtual void Close_Socket() = 0;
    virtual void Set_Security_Options() {};
    virtual ~ISocket() = default;
};


#endif //SERVER_ISOCKET_H
