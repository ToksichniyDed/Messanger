#include <iostream>

int main() {
    system("chcp 65001");
    try {
    }
    catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
    }
}
