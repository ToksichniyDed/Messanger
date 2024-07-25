#include <iostream>
#include <boost/di.hpp>

#include "Modules/Model/Networking/Socket/Socket.h"
#include "Message_Factory_Config.h"
#include "Modules/View/Main_View.h"

int main() {
    system("chcp 65001");
    try {
        auto client = Socket::Instance();
        client->Socket_Start();

        auto UI_injector = boost::di::make_injector();
        auto main_view = UI_injector.create<std::unique_ptr<Main_View>>();
        main_view->Start_UI();
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
    }
}
