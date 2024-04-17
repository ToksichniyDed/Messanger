//
// Created by Toksichniy_Ded on 08.04.2024.
//

#ifndef CLIENT_REGISTER_H
#define CLIENT_REGISTER_H

#include <iostream>

class Register {
public:
    [[nodiscard]] std::string Set_Telephone_Number() const;
    [[nodiscard]] std::string Set_Password() const;
};

inline std::string Register::Set_Telephone_Number() const {
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
        return "";
    }
    return telephone_number;
}

inline std::string Register::Set_Password() const {
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
        return "";
    }
    return password;
}


#endif //CLIENT_REGISTER_H
