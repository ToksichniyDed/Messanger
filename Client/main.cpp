#include <iostream>
#include <boost/di.hpp>

#include "Modules/Model/Networking/Socket/Socket.h"
#include "Message_Factory_Config.h"
#include "Modules/View/Main_View.h"

int main() {
    system("chcp 65001");
    try {
        auto client_injector = boost::di::make_injector(
                boost::di::bind<TFactory<std::string, IMessage>>.to([] {
                    return std::make_unique<TFactory<std::string, IMessage>>(
                            Message_Factory_Config::Message_Factory_Config());
                }),
                boost::di::bind<Message_From_Server_Queue>.to([]{
                    return Message_From_Server_Queue::Instance();
                }),
                boost::di::bind<Message_To_Server_Queue>.to([]{
                    return Message_To_Server_Queue::Instance();
                }),
                boost::di::bind<Socket_Manager>.to([]{return nullptr;})
                );
        auto client = client_injector.create<std::unique_ptr<Socket>>();
        //auto client = std::make_unique<Socket>();
        client->Socket_Start();

        auto UI_injector = boost::di::make_injector();
        auto main_view = UI_injector.create<std::unique_ptr<Main_View>>();
        main_view->Start_UI();
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
    }
}
