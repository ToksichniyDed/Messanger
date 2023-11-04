//
// Created by super on 09.09.2023.
//

#include "UserInterface.h"

UserInterface::UserInterface() = default;
UserInterface* UserInterface::m_instance;

int UserInterface::Menu() {
    //system("cls");
    std::cout<< "Меню\n"<<"1. Регистрация \n"<<"2. Авторизация \n"<<"3. Выйти\n"<<std::endl;
    int menu_item;
    try {
        std::cin>>menu_item;
        if (isalpha(menu_item))
            throw std::runtime_error("Only digits are allowed.");
        switch (menu_item) {
                case 1: {
                    return 1;
                }
                case 2: {
                    return 2;
                }
                case 3: {
                    return 3;
                }
                default: {
                    std::cout << "Пункт меню отсутствует!" << std::endl;
                    return 0;
                }
            }
    } catch (std::exception &Error) {
        std::cout << "Error: " << Error.what() << std::endl;
        return 0;
    }
}

UserInterface *UserInterface::GetInstance() {
    if(m_instance == nullptr) {
        m_instance = new UserInterface();
    }
    return m_instance;
}

std::string UserInterface::Registration_Authorization() {
    std::string telephone_number = " ",password = " ";
    while(telephone_number == " "){
        telephone_number = Get_Telephone_Number();
    }
    while(password == " "){
        password = Get_Password();
    }
    boost::property_tree::ptree registration_data_pt;
    registration_data_pt.put("telephone_number", telephone_number);
    registration_data_pt.put("password", password);

    std::stringstream ss;
    boost::property_tree::write_json(ss, registration_data_pt);
    std::string registration_authorization_data = ss.str();
    return registration_authorization_data;
}

std::string UserInterface::Get_Password() {
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


std::string UserInterface::Get_Telephone_Number() {
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






