//
// Created by super on 08.09.2023.
//

#ifndef SERVER_CLIENTHANDLER_H
#define SERVER_CLIENTHANDLER_H

#include <iostream>
#include <winsock2.h>
#include <queue>
#include <mutex>

#include "../Tools/Json_Tools.h"

class ClientHandler {

private:
    SOCKET m_client_socket;
    static std::queue<std::string> m_message_queue;

public:
    [[maybe_unused]] explicit ClientHandler(SOCKET client_socket);
    void Read_Client_Data(std::vector<char> client_buffer) const;
    void Send_Data_To_Client(const std::string &type, const std::string &message) const;
};


#endif //SERVER_CLIENTHANDLER_H
