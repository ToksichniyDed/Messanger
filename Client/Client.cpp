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
    while(!Registration())
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

bool Client::Registration() {
    std::string telephone_number = " ",password = " ";
    while(telephone_number == " "){
        telephone_number = Get_Telephone_Number();
    }
    while(password == " "){
        password = Get_Password();
    }
    boost::property_tree::ptree registration_data_pt;
    registration_data_pt.put("telephone_number", telephone_number);
    registration_data_pt.put("password", password);

    std::stringstream ss;
    boost::property_tree::write_json(ss, registration_data_pt);
    std::string registration_data = ss.str();
    m_server_handler->Write_to_Server("registration_data", registration_data);
}

std::string Client::Get_Password() {
    std::wcout.imbue(std::locale(""));
    std::cout << "Введите пароль: ";
    std::string password;
    try {
        std::getline(std::cin, password);

        // Проверяем наличие пробелов или русских символов
        for (wchar_t c : password) {
            if (c == L' ' || (c >= L'а' && c <= L'я') || (c >= L'А' && c <= L'Я')) {
                throw std::runtime_error("Пароль содержит недопустимые символы.");
            }
        }
    } catch (std::exception &Error) {
        std::cout << Error.what() << std::endl;
        return " ";
    }
    return password;
}


std::string Client::Get_Telephone_Number() {
    std::cout << "Введите номер телефона: ";
    std::string telephone_number;
    try {
        std::getline(std::cin, telephone_number);

        for (char c: telephone_number) {
            if (!isdigit(c)) {
                throw std::runtime_error("Номер содержит недопустимые символы");
            }
        }
    } catch (std::exception &Error) {
        std::cout << Error.what() << std::endl;
        return " ";
    }
    return telephone_number;
}




