#include <iostream>

#include "Server.h"

int main() {
    system("chcp 65001");

    try {
        // Инициализация Winsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Failed to initialize Winsock." << std::endl;
            return 1;
        }

        std::unique_ptr<Server> main_server (Server::GetInstance());
        main_server->Start();
        main_server->Listening();
        main_server->Turn_Off();
        WSACleanup();
    }
    catch(std::exception& Error ){
        std::cout<<"Error: "<< Error.what()<<std::endl;
    }

    return 0;

}
