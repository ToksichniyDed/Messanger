//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_REPOSITORY_H
#define SERVER_REPOSITORY_H

#include "Pool/Database_Connector.h"
#include "../../Tools/OpenSSL_Tools.h"
#include "Database_Handlers/include/User_Handler.h"
#include "Database_Handlers/include/Password_Handler.h"

class Repository {
protected:
    std::unique_ptr<User_Handler> m_user_handler;
    std::unique_ptr<Password_Handler> m_password_handler;

public:
    explicit Repository(std::unique_ptr<User_Handler> u_handler, std::unique_ptr<Password_Handler> p_handler);
    bool User_Registration (std::shared_ptr<IDatabase_Connector> connector, std::shared_ptr<User> user,  std::shared_ptr<Password> password);
    bool User_Authorization(std::shared_ptr<IDatabase_Connector> connector, std::shared_ptr<User> user,  std::shared_ptr<Password> password);

};


#endif //SERVER_REPOSITORY_H
