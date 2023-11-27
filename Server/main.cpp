#include <iostream>
#include <thread>

#include "Network/Socket/Server_Socket/Server_Socket.h"
#include "Business_Logic/Database/Database_Connector.h"

int main() {
    system("chcp 65001");

    try {
        // Инициализация Winsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Failed to initialize Winsock." << std::endl;
            return 1;
        }

        auto server = std::make_unique<Server_Socket>();
        auto database_connector = std::make_unique<Database_Connector>();
        server->Open_Socket();
        database_connector->Connect("Plotniy_Messanger","localhost","","127.0.0.1","8080");
        std::thread accept_thread([&]{server->Accept();});
        WSACleanup();
    }
    catch(std::exception& Error ){
        std::cout<<"Error: "<< Error.what()<<std::endl;
    }



    return 0;

}
