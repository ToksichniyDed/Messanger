#include <iostream>
#include <boost/di.hpp>

#include "Modules/Model/Networking/Socket/Socket.h"
#include "Message_Factory_Config.h"
#include "Modules/View/Main_View.h"

int main() {
    system("chcp 65001");
    try {
        auto client = Socket::Instance();
        //auto client = std::make_unique<Socket>();
        client->Socket_Start();

        auto UI_injector = boost::di::make_injector(
                boost::di::bind<Message_To_Server_Queue>.to([] {
                    return Message_To_Server_Queue::Instance();
                })
        );
        auto main_view = UI_injector.create<std::unique_ptr<Main_View>>();
        main_view->Start_UI();
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
    }
}
