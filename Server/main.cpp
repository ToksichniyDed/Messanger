#include <iostream>
#include <thread>

#include "Modules/Network/Socket/Server_Socket/Server_Socket.h"
#include "Modules/Business_Logic/Database/Pool/Database_Connector.h"
#include "Modules/Business_Logic/Task/include/Task_Factory.h"
#include "Modules/Thread/Pool/Task_Container.h"

void Start_Server(Database_Connector* connector);
void Connect_Database(Database_Connector* connector);
void Manage_Server();
void Manage_Database_Connection();

int main() {
    system("chcp 65001");

    Database_Connector* connector;
    std::thread database_connection_thread(Connect_Database, connector);
    std::thread main_thread(Start_Server, connector);

    main_thread.join();
    database_connection_thread.join();

    return 0;
}

//Запускаю сервер. Создается серверный сокет, биндиться, включаается режим прослушивания (внутри метода Open()).
//Создается 2 потока: поток для метода Accept() (прием новых подключений),
//поток для метода Listening_Clients_Socket()(прослушивание подключенных клиентов на предмет сообщений или нарушения соединения).
void Start_Server(Database_Connector* connector){
    Container_Vector<Client_Socket*> containerVector;
    Task_Container taskContainer;
    Task_Factory taskFactory;
    taskFactory.Set_DB_Connector(connector);
    Client_Manager clientManager(&containerVector, &taskContainer, &taskFactory);
    Server_Socket server(&clientManager);
    server.Open_Socket();
    std::thread accept_thread([&]{server.Accept();});
    std::thread listening_clients_thread([&]{server.Listening_Clients_Socket();});
    accept_thread.join();
    listening_clients_thread.join();
}


//Подключение к базе данных
void Connect_Database(Database_Connector* connector){
    Database_Connector database_connector;
    connector = &database_connector;
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