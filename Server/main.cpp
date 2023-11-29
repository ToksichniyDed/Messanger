#include <iostream>
#include <thread>

#include "Network/Socket/Server_Socket/Server_Socket.h"
#include "Business_Logic/Database/Database_Connector.h"

void Start_Server();
void Connect_Database();
void Manage_Server();
void Manage_Database_Connection();

int main() {
    system("chcp 65001");

    std::thread database_connection_thread(Connect_Database);
    std::thread main_thread(Start_Server);

    main_thread.join();
    database_connection_thread.join();

    return 0;
}

void Start_Server(){
    Server_Socket server;
    server.Open_Socket();
    std::thread accept_thread([&]{server.Accept();});
    std::thread listening_clients_thread([&]{server.Listening_Clients_Socket();});
    accept_thread.join();
    listening_clients_thread.join();
}

void Connect_Database(){
    Database_Connector database_connector;
    if(database_connector.Connect("Plotniy_Messanger","postgres","password","127.0.0.1","5432"))
        std::cout<<"Successful connection to database!"<<std::endl;
    else
        std::cout<<"Unsuccessful connection to database!"<<std::endl;
    while(database_connector.IsConnected())
    {

    }
}

void Manage_Server(){

}

void Manage_Database_Connection(){

}