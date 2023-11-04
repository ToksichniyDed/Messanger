//
// Created by super on 10.09.2023.
//

#include "Client.h"

Client::Client() = default;
Client* Client::m_instance;

void Client::Connect() {
    m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_socket == -1)
        throw std::runtime_error("Failed create socket!");

    m_server_address.sin_family = AF_INET;
    m_server_address.sin_port = htons(8080);
    m_server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    m_server_handler = ServerHandler::GetInstance(m_server_socket);
    m_mediator = User_ServerHandler_Mediator::Get_Instance();
    m_server_handler->Set_Mediator(m_mediator);

    if (connect(m_server_socket, (struct sockaddr *) &m_server_address, sizeof(m_server_address)) == -1){
        Disconnect();
        throw std::runtime_error("Failed connect to server");
    }

    std::cout << "Successful connect to server! Socket: " << m_server_socket << std::endl;
}

void Client::Disconnect() const {
    closesocket(m_server_socket);
}

bool Client::Is_Connected() const {
    while(true) {
        boost::property_tree::ptree client_pt;
        client_pt.put("type", "check_connection");

        std::stringstream ss;
        boost::property_tree::write_json(ss, client_pt);

        std::string buffer = ss.str();
        int check_server = send(m_server_socket, buffer.c_str(), buffer.size(), 0);
        if (check_server < 0)
            return false;
        return true;
    }
}

bool Client::Start_Communication() {
    m_user = new User();
    m_user->Set_Mediator(m_mediator);
    switch(){
        case '1'
    }
    if(m_user->User_Registration_Authorization( "registration_data"))
        std::cout<<"Успешная регистрация!"<<std::endl;
    else
        std::cout<<"Ошибка регистрации!"<<std::endl;

    if(m_user->User_Registration_Authorization( "authorization_data"))
        std::cout<<"Успешная авторизация!"<<std::endl;
    else
        std::cout<<"Ошибка авторизации!"<<std::endl;
    return true;
}

Client*  Client::GetInstance() {
    if(m_instance == nullptr)
        m_instance = new Client();
    return m_instance;
}

ServerHandler *Client::Get_ServerHandler() {
    return m_server_handler;
}








