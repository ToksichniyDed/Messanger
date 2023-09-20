//
// Created by super on 09.09.2023.
//

#include "UserInterface.h"

UserInterface::UserInterface() = default;
UserInterface* UserInterface::m_instance;

int UserInterface::Menu() {
    //system("cls");
    std::cout<< "Меню\n"<<"1. Поприветствовать сервер!\n"<<"2. Что то еще\n"<<"3. Выйти\n"<<std::endl;
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





