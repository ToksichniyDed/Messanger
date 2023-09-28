//
// Created by super on 10.09.2023.
//

#include "Client.h"

Client::Client() = default;
Client* Client::m_instance;

void Client::Connect() {
    m_client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_client_socket == -1)
        throw std::runtime_error("Failed create socket!");

    m_server_address.sin_family = AF_INET;
    m_server_address.sin_port = htons(8080);
    m_server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    m_server_handler = ServerHandler::GetInstance(m_client_socket);

    if (connect(m_client_socket, (struct sockaddr *) &m_server_address, sizeof(m_server_address)) == -1){
        Disconnect();
        throw std::runtime_error("Failed connect to server");
    }

    std::cout << "Successful connect to server! Socket: " << m_client_socket<<  std::endl;
}

void Client::Disconnect() const {
    closesocket(m_client_socket);
}

bool Client::Is_Connected() const {
    while(true) {
        boost::property_tree::ptree client_pt;
        client_pt.put("type", "check_connection");

        std::stringstream ss;
        boost::property_tree::write_json(ss, client_pt);

        std::string buffer = ss.str();
        int check_server = send(m_client_socket, buffer.c_str(), buffer.size(), 0);
        if (check_server < 0)
            return false;
        return true;
    }
}

bool Client::Start_Communication() {
    while(true){
        switch (m_server_handler->Get_User_Interface()->Menu()) {
            case 0:
                break;
            case 1:{
                Write_Message();
                break;
            }
            case 2:{
                break;
            }
            case 3:{
                Disconnect();
                return false;
            }
            default:{
                break;
            }
        }
    }
}

Client*  Client::GetInstance() {
    if(m_instance == nullptr)
        m_instance = new Client();
    return m_instance;
}

void Client::Write_Message() {
    std::string message;
    std::cout<<"Введите сообщение: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, message);
    m_server_handler->Write_to_Server("message",message);
}




