//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_REPOSITORY_H
#define SERVER_REPOSITORY_H

#include "Database_Handlers/include/Handlers_Headers.h"
#include "Pool/Database_Connector.h"
#include "../../Tools/OpenSSL_Tools.h"

class Repository {
protected:
    User_Handler* m_user_handler;
    Password_Handler* m_password_handler;

public:
    explicit Repository(User_Handler* u_handler = new User_Handler, Password_Handler* p_handler = new Password_Handler);
    bool User_Registration (Database_Connector* connector, User* user,  Password* password);
    bool User_Authorization(Database_Connector* connector, User* user, Password* password);

};


#endif //SERVER_REPOSITORY_H
