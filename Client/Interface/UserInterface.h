//
// Created by super on 09.09.2023.
//

#ifndef CLIENT_USERINTERFACE_H
#define CLIENT_USERINTERFACE_H

#include <iostream>
#include <memory>
#include <conio.h>


class UserInterface {
private:
    static UserInterface* m_instance;
    UserInterface();

public:
    static UserInterface* GetInstance();
    static int Menu();
};


#endif //CLIENT_USERINTERFACE_H
