//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_PASSWORD_HANDLER_H
#define SERVER_PASSWORD_HANDLER_H

#include "../../DataMappers/PasswordMapper.h"
#include "../../Tables/User.h"
#include "../../Pool/Database_Connector.h"

class Password_Handler {
protected:
    Database_Connector* m_connector;
    PasswordMapper* m_mapper;

public:
    explicit Password_Handler(Database_Connector* connector = nullptr, PasswordMapper* mapper = nullptr):
    m_connector(connector), m_mapper(mapper){}
    void Set_Connector(Database_Connector* connector);
    void Disconnect_Connector();
    bool Create(Password& password);
    Password Read_By_UserID(Password& password);
    bool Update_Salt(Password& password);
    bool Update_Hash(Password& password);
    bool Delete(Password& password);
};


#endif //SERVER_PASSWORD_HANDLER_H
