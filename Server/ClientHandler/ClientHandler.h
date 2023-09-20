//
// Created by super on 08.09.2023.
//

#ifndef SERVER_CLIENTHANDLER_H
#define SERVER_CLIENTHANDLER_H

#include <iostream>
#include <winsock2.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class ClientHandler {

private:
    SOCKET m_client_socket;

public:
    explicit ClientHandler(SOCKET client_socket);
    void Read_Client_Data();
    void Send_Data_To_Client();
    bool Check_Connection_With_Client() const;
    void Start_Handle();
};


#endif //SERVER_CLIENTHANDLER_H
