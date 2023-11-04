//
// Created by super on 03.11.2023.
//

#ifndef CLIENT_USER_SERVERHANDLER_MEDIATOR_H
#define CLIENT_USER_SERVERHANDLER_MEDIATOR_H

#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>

#include "../Tools/Json_Tools.h"

class User_ServerHandler_Mediator{
private:
    static User_ServerHandler_Mediator* m_instance;

    //Мьютексы
    std::mutex m_access_to_message_to_server_queue;
    std::mutex m_access_to_message_from_server_queue;
    std::mutex m_access_to_once_used_data_from_server;

    //Условные переменные
    std::condition_variable m_cv_to_serverhandler;
    std::condition_variable m_cv_to_user;
    std::condition_variable m_cv_to_once_used_data;

    //Контейнеры
    std::queue<std::string> m_message_to_server_queue;
    std::queue<std::string> m_message_from_server_queue;
    std::queue<std::string> m_once_used_data_from_server_queue;

public:
    static User_ServerHandler_Mediator* Get_Instance();
    ~User_ServerHandler_Mediator(){delete m_instance;}
    bool Message_To_User_Queue_Is_Empty();
    bool Message_To_Server_Queue_Is_Empty();
    void Handle_Data_From_ServerHandler();

    //Положить в контейнер
    void Set_Data_To_User_From_ServerHandler(const std::string& response);
    void Set_Data_To_ServerHandler_From_User(std::string& type, std::string& message);

    //Забрать из контейнера
    std::string Get_Data_To_ServerHandler_From_User();
    std::string Get_Once_Used_Data_To_User_From_ServerHandler(std::string& type);

    //SetterЫ
    template <typename ContainerType, typename MutexType>
    void Set_To_Queue(const std::string &str, ContainerType &container, MutexType &mutex);

    //Getterы
    std::condition_variable& Get_CV_To_ServerHandler();
    std::condition_variable &Get_CV_To_User();
    std::condition_variable &Get_CV_To_Once_Used();

};

#endif //CLIENT_USER_SERVERHANDLER_MEDIATOR_H
