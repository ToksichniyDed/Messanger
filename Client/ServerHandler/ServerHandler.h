//
// Created by super on 09.09.2023.
//

#ifndef CLIENT_SERVERHANDLER_H
#define CLIENT_SERVERHANDLER_H

#include <winsock2.h>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "D:\Progg\Plotniy_Project\Client\Interface\UserInterface.h"

class ServerHandler {
private:
    UserInterface* m_interface = UserInterface::GetInstance();
    static ServerHandler* m_instance;
    static std::queue<std::string> m_message_to_server_queue;
    static std::queue<std::vector<char>> m_message_from_server_queue;
    std::mutex m_access_to_message_to_server_queue;
    std::mutex m_access_to_message_from_server_queue;
    explicit ServerHandler(SOCKET client_socket);
    SOCKET m_server_socket;

public:
    static ServerHandler* GetInstance(SOCKET client_socket);
    ~ServerHandler(){delete m_interface;}
    void Handle_Server_Message();
    void Read_from_Server();
    void Write_to_Server(std::string type, const std::string& message);
    UserInterface* Get_User_Interface();

};



#endif //CLIENT_SERVERHANDLER_H
