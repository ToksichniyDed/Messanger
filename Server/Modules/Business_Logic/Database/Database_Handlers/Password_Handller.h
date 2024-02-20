//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_PASSWORD_HANDLLER_H
#define SERVER_PASSWORD_HANDLLER_H

#include "../DataMappers/PasswordMapper.h"
#include "../Tables/User.h"
#include "../Pool/Database_Connector.h"

class Password_Handller {
protected:
    Database_Connector* m_connector;
    PasswordMapper* m_mapper;

public:
    bool Create(Password& password);
    Password Read_By_UserID(Password& password);
    bool Update_Salt(Password& password);
    bool Update_Hash(Password& password);
    bool Delete(Password& password);
};


#endif //SERVER_PASSWORD_HANDLLER_H
