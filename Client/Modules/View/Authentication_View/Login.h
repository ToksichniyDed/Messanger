//
// Created by super on 30.11.2023.
//

#ifndef CLIENT_LOGIN_H
#define CLIENT_LOGIN_H

#include <iostream>

class Login {
protected:
    std::string Get_Telephone_Number();
    std::string Get_Password();
};

std::string Login::Get_Telephone_Number() {
    std::cout << "Введите номер телефона: ";
    std::string telephone_number;
    try {
        std::getline(std::cin, telephone_number);

        for (char c: telephone_number) {
            if (!isdigit(c)) {
                throw std::runtime_error("Номер содержит недопустимые символы");
            }
        }
    } catch (std::exception &Error) {
        std::cout << Error.what() << std::endl;
        return " ";
    }
    return telephone_number;
}

std::string Login::Get_Password() {
    std::wcout.imbue(std::locale(""));
    std::cout << "Введите пароль: ";
    std::string password;
    try {
        std::getline(std::cin, password);

        // Проверяем наличие пробелов или русских символов
        for (wchar_t c : password) {
            if (c == L' ' || (c >= L'а' && c <= L'я') || (c >= L'А' && c <= L'Я')) {
                throw std::runtime_error("Пароль содержит недопустимые символы.");
            }
        }
    } catch (std::exception &Error) {
        std::cout << Error.what() << std::endl;
        return " ";
    }
    return password;
}


#endif //CLIENT_LOGIN_H
