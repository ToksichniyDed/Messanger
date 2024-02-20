//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_REPOSITORY_H
#define SERVER_REPOSITORY_H

#include "Database_Handlers/User_Handler.h"
#include "Database_Handlers/Password_Handller.h"

class Repository {
protected:
    User_Handler* m_user_handler;
    Password_Handller* m_password_handler;

public:
    bool User_Registration();
    bool User_Authorization();

};


#endif //SERVER_REPOSITORY_H
