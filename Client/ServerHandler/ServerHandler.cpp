//
// Created by super on 09.09.2023.
//

#include "ServerHandler.h"

ServerHandler* ServerHandler::m_instance;

ServerHandler::ServerHandler(SOCKET client_socket):m_client_socket(client_socket){}

void ServerHandler::Read_from_Server() {

}

void ServerHandler::Write_to_Server() const {

        try {
            boost::property_tree::ptree client_pt;
            client_pt.put("type","message");
            client_pt.put("data","Привет сервер!");

            std::stringstream ss;
            boost::property_tree::write_json(ss,client_pt);

            std::string message_to_server = ss.str();

            int sent_bytes = send(m_client_socket, message_to_server.c_str(), message_to_server.length(), 0);
            if(sent_bytes < 0){
                throw std::runtime_error ("Failed to send message!");}
        }
    catch (std::exception& Error){
        std::cout<<"Error: "<<Error.what()<<std::endl;
        return;
    }

}

ServerHandler* ServerHandler::GetInstance(SOCKET client_socket) {
    if(m_instance == nullptr)
        m_instance = new ServerHandler(client_socket);

    return m_instance;
}

UserInterface *ServerHandler::Get_User_Interface() {
    return m_interface;
}

