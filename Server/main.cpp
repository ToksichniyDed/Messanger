#include <iostream>
#include <thread>
#include <boost/di.hpp>

#include "Modules/Thread/Thread.h"
#include "Modules/Thread/Pool/Thread_Pool.h"
#include "Modules/Network/Socket/Server_Socket/Server_Socket.h"

#include "Task_Factory_Config.h"
#include "Message_Factory_Config.h"
#include "Pool_Connection_Config.h"

void Start_Server();

int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    try{
    Start_Server();}catch (std::exception &Error){
        std::cout<<"Error: "<<Error.what()<<std::endl;
    }
    return 0;
}

//Запускаю сервер. Создается серверный сокет, биндиться, включаается режим прослушивания (внутри метода Open()).
//Создается 2 потока: поток для метода Accept() (прием новых подключений),
//поток для метода Listening_Clients_Socket()(прослушивание подключенных клиентов на предмет сообщений или нарушения соединения).
void Start_Server(){
    auto pool_connection = Pool_Connection_Config();

    auto task_factory = std::make_unique<Task_Factory>(std::move(pool_connection));

    auto task_container = std::make_shared<Task_Container>();

    auto thread_pool = std::make_unique<Thread_Pool>(5,task_container);

    auto client_manager = std::make_unique<Client_Manager>(nullptr, task_container, std::move(task_factory), std::move(Message_Factory_Config()));

    auto server_socket = std::make_unique<Server_Socket>(std::move(client_manager));

    std::unique_ptr<std::thread> server_thread = std::make_unique<std::thread>([&]{server_socket->Open_Socket();
    auto listening_thread = std::make_unique<std::thread>([&]{server_socket->Listening_Clients_Socket();});
    auto accept_thread = std::make_unique<std::thread>([&]{server_socket->Accept();});

    accept_thread->join();
    listening_thread->join();
    });

    server_thread->join();
}