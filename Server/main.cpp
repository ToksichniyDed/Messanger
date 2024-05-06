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
    try {
        Start_Server();
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
    }
    return 0;
}

//Запускаю сервер. Создается серверный сокет, биндиться, включаается режим прослушивания (внутри метода Open()).
//Создается 2 потока: поток для метода Accept() (прием новых подключений),
//поток для метода Listening_Clients_Socket()(прослушивание подключенных клиентов на предмет сообщений или нарушения соединения).
void Start_Server() {
    auto pool_connection = Pool_Connection_Config();

    auto task_container = std::make_shared<Task_Container>();

    auto inj = boost::di::make_injector(
            boost::di::bind<int>.to(2),
            boost::di::bind<Task_Container>.to(task_container),
//            boost::di::bind<Thread_Creator>.to([] {
//                std::unique_ptr<Thread_Creator> temp = std::make_unique<Real_Thread_Creator>();
//                return temp;
//            }),
            boost::di::bind<Thread_Creator>().to<Real_Thread_Creator>(),
            boost::di::bind<Container_Vector<std::unique_ptr<IThread>>>.to([] {
                return std::make_unique<Container_Vector<std::unique_ptr<IThread>>>();
            }),
            boost::di::bind<Container_Vector<std::shared_ptr<Client_Socket>>>.to([]{return std::make_unique<Container_Vector<std::shared_ptr<Client_Socket>>>();}),
            boost::di::bind<Task_Factory>().to([&]{return Task_Factory_Config(std::move(pool_connection));}),
            boost::di::bind<Message_Factory>.to([]{return Message_Factory_Config();})
    );

    auto thread_pool = inj.create<std::unique_ptr<Thread_Pool>>();

    auto client_manager = inj.create<std::unique_ptr<Client_Manager>>();

    auto server_socket = std::make_unique<Server_Socket>(std::move(client_manager));

    std::unique_ptr<std::thread> server_thread = std::make_unique<std::thread>([&] {
        server_socket->Open_Socket();
        auto listening_thread = std::make_unique<std::thread>([&] { server_socket->Listening_Clients_Socket(); });
        auto accept_thread = std::make_unique<std::thread>([&] { server_socket->Accept(); });

        accept_thread->join();
        listening_thread->join();
    });

    server_thread->join();
}

void Create_Task_Container() {

}