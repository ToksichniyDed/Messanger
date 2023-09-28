#include <iostream>
#include <thread>
#include <chrono>

#include "Client.h"

int main() {
    system("chcp 65001");

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    bool flag = true;
    while(flag) {
        try {
            auto client = std::unique_ptr<Client>(Client::GetInstance());
            client->Connect();
            std::thread check_thread([&]{bool flag = true;
                while(flag){flag = client->Is_Connected();
            std::this_thread::sleep_for(std::chrono::seconds(5));}
                throw std::runtime_error("Server disconnected!");});
            flag = client->Start_Communication();
        }
        catch (std::exception &Error) {
            std::cout << "Error: " << Error.what() << std::endl;
            flag = true;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}
