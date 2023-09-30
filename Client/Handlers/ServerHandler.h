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
#include <iostream>
#include <map>
#include <condition_variable>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class ServerHandler {
private:
    //мьютексы и условные переменные
    std::mutex m_access_to_message_to_server_queue;
    std::mutex m_access_to_message_from_server_queue;
    std::mutex m_access_to_handle_message_from_server_queue;
    std::condition_variable m_conditional_variable;

    //Контейнеры
    std::queue<std::string> m_message_to_server_queue;
    std::queue<std::vector<char>> m_message_from_server_queue;
    std::vector<std::pair<std::string,std::string>> m_handle_message_from_server_queue;

    //Переменные
    SOCKET m_server_socket;

    static ServerHandler* m_instance;
    explicit ServerHandler(SOCKET client_socket);


public:
    static ServerHandler* GetInstance(SOCKET client_socket);
    ~ServerHandler(){delete m_instance;}
    void Handle_Server_Message();
    std::mutex& Get_Access_To_Handle_Message_From_Server_Queue_Mutex();
    std::condition_variable& Get_Conditional_Variable();
    std::vector<std::pair<std::string,std::string>>& Get_Handle_Message_From_Server_Queue();

    //Общение с сервером
    void Read_from_Server();
    void Write_to_Server(std::string type, const std::string& message);

};


#endif //CLIENT_SERVERHANDLER_H
