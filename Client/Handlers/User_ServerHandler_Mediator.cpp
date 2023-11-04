//
// Created by super on 03.11.2023.
//

#include "User_ServerHandler_Mediator.h"

User_ServerHandler_Mediator* User_ServerHandler_Mediator::m_instance;

User_ServerHandler_Mediator *User_ServerHandler_Mediator::Get_Instance() {
    if(m_instance == nullptr)
        m_instance = new User_ServerHandler_Mediator();
    return m_instance;
}

std::string User_ServerHandler_Mediator::Get_Data_To_ServerHandler_From_User() {
    std::unique_lock<std::mutex> lock(m_access_to_message_to_server_queue);
    std::string temp = m_message_to_server_queue.front();
    m_message_to_server_queue.pop();
    return temp;
}

std::string User_ServerHandler_Mediator::Get_Once_Used_Data_To_User_From_ServerHandler(std::string& type) {
    std::unique_lock<std::mutex> lock(m_access_to_once_used_data_from_server);
    while (!m_once_used_data_from_server_queue.empty()) {
        std::string temp = m_once_used_data_from_server_queue.front();
        try {
            auto message_type = Unpack_Json("type", temp);
            if (message_type == type) {
                m_once_used_data_from_server_queue.pop();
                auto message_data = Unpack_Json("data", temp);
                return message_data;
            }
        } catch (const std::exception& Error) {
            std::cout << "Error: " << Error.what() << std::endl;
        }
    }
    return "";
}

void User_ServerHandler_Mediator::Set_Data_To_User_From_ServerHandler(const std::string& response) {
    Set_To_Queue(response,m_message_from_server_queue, m_access_to_message_from_server_queue);
    this->Handle_Data_From_ServerHandler();
}

void User_ServerHandler_Mediator::Handle_Data_From_ServerHandler() {
    std::string response;
    {
        std::unique_lock<std::mutex> lock(m_access_to_message_from_server_queue);
        response = m_message_from_server_queue.front();
        m_message_from_server_queue.pop();}

    try {
        auto message_type = Unpack_Json("type",response);
        if (message_type == "check")
        {}
        else if(message_type == "registration_data_ans") {
            Set_To_Queue(response, m_once_used_data_from_server_queue,m_access_to_once_used_data_from_server);
            m_cv_to_once_used_data.notify_all();
            return;
        }
        else if(message_type == "authorization_data_ans") {
            Set_To_Queue(response, m_once_used_data_from_server_queue,m_access_to_once_used_data_from_server);
            m_cv_to_once_used_data.notify_all();
            return;
        }
        else
            std::cout << "No handle for this type of message!" << std::endl;
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
    }
}

void User_ServerHandler_Mediator::Set_Data_To_ServerHandler_From_User(std::string& type, std::string &message) {
    try{
        std::string message_to_server = Pack_Json(type,message);
        Set_To_Queue(message_to_server, m_message_to_server_queue,m_access_to_message_to_server_queue);
        m_cv_to_serverhandler.notify_one();
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return;
    }
}

std::condition_variable& User_ServerHandler_Mediator::Get_CV_To_ServerHandler() {
    return m_cv_to_serverhandler;
}

std::condition_variable& User_ServerHandler_Mediator::Get_CV_To_User() {
    return m_cv_to_user;
}

std::condition_variable& User_ServerHandler_Mediator::Get_CV_To_Once_Used() {
    return m_cv_to_once_used_data;
}

bool User_ServerHandler_Mediator::Message_To_Server_Queue_Is_Empty() {
    if([&](){std::unique_lock<std::mutex> lock(m_access_to_message_to_server_queue);
        return (m_message_to_server_queue.empty());}())
        return true;
    return false;
}

bool User_ServerHandler_Mediator::Message_To_User_Queue_Is_Empty() {
    if([&](){std::unique_lock<std::mutex> lock(m_access_to_message_from_server_queue);
        return (!m_message_from_server_queue.empty());}())
        return true;
    return false;
}

template <typename ContainerType, typename MutexType>
void User_ServerHandler_Mediator::Set_To_Queue(const std::string &str, ContainerType &container, MutexType &mutex) {
    std::unique_lock<MutexType> lock(mutex);
    container.emplace(str);
}

