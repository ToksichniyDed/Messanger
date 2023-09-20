//
// Created by super on 09.09.2023.
//

#ifndef CLIENT_SERVERHANDLER_H
#define CLIENT_SERVERHANDLER_H

#include <winsock2.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "D:\Progg\Plotniy_Project\Client\Interface\UserInterface.h"

class ServerHandler {
private:
    UserInterface* m_interface = UserInterface::GetInstance();
    static ServerHandler* m_instance;
    explicit ServerHandler(SOCKET client_socket);
    SOCKET m_client_socket;

public:
    static ServerHandler* GetInstance(SOCKET client_socket);
    ~ServerHandler(){delete m_interface;}
    void Read_from_Server();
    void Write_to_Server() const;
    UserInterface* Get_User_Interface();

};



#endif //CLIENT_SERVERHANDLER_H
