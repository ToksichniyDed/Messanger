//
// Created by Toksichniy_Ded on 09.04.2024.
//

#include "Main_View.h"

void Main_View::Start_UI() {
    Enter_View();
    while(!m_exit){

    }
}

void Main_View::Enter_View() {
    bool flag = true;
    while(flag) {
        std::cout << "1. Регистрация\n"
                     "2. Авторизация\n"
                     "3. Выход\n";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
            case 1: {
                m_registration->Start_Registration();
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                flag = false;
                m_exit = false;
                break;
            }
            default: {
                std::cout<<"Нет такого пункта! Попробуйте еще раз!"<<std::endl;
                break;
            }
        }
    }
}

Main_View::Main_View(Main_View::Registration registration):m_registration(std::move(registration)) {

}
