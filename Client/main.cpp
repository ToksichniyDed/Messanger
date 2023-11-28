#include <iostream>

#include "Model/Networking/Socket/Socket.h"

int main() {
    system("chcp 65001");

    bool flag = true;
    while(flag) {
        try {
            auto client_socket = std::make_unique<Socket>();
            client_socket->Socket_Start();
        }
        catch (std::exception &Error) {
            std::cout << "Error: " << Error.what() << std::endl;
        }
    }
}
