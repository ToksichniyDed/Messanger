//
// Created by super on 09.09.2023.
//

#ifndef CLIENT_USERINTERFACE_H
#define CLIENT_USERINTERFACE_H

#include <iostream>
#include <memory>
#include <conio.h>
#include <locale>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


class UserInterface {
private:
    static UserInterface* m_instance;
    UserInterface();

public:
    static UserInterface* GetInstance();

    //Авторизация и регистрация
    bool Authorization();
    std::string Registration();
    std::string Get_Password();
    std::string Get_Telephone_Number();


    //Главное меню и подпункты меню
    static int Menu();
};


#endif //CLIENT_USERINTERFACE_H
