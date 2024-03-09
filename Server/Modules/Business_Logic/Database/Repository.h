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
    std::unique_ptr<User_Handler> m_user_handler;
    std::unique_ptr<Password_Handler> m_password_handler;

public:
    explicit Repository(std::unique_ptr<User_Handler> u_handler = std::make_unique<User_Handler>(), std::unique_ptr<Password_Handler> p_handler = std::make_unique<Password_Handler>());
    bool User_Registration (std::shared_ptr<IDatabase_Connector> connector, std::shared_ptr<User> user,  std::shared_ptr<Password> password);
    bool User_Authorization(std::shared_ptr<IDatabase_Connector> connector, std::shared_ptr<User> user,  std::shared_ptr<Password> password);

};


#endif //SERVER_REPOSITORY_H
