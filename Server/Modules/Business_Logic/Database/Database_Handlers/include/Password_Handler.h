//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_PASSWORD_HANDLER_H
#define SERVER_PASSWORD_HANDLER_H

#include <utility>

#include "../../DataMappers/PasswordMapper.h"
#include "../../Tables/User.h"
#include "../../Pool/Database_Connector.h"

class Password_Handler {
protected:
    std::shared_ptr<IDatabase_Connector> m_connector;
    std::unique_ptr<PasswordMapper> m_mapper;

public:
    explicit Password_Handler(std::shared_ptr<IDatabase_Connector> connector = nullptr, std::unique_ptr<PasswordMapper> mapper = nullptr):
    m_connector(std::move(connector)), m_mapper(std::move(mapper)){}
    void Set_Connector(std::shared_ptr<IDatabase_Connector> connector);
    void Disconnect_Connector();
    bool Create(Password& password);
    Password Read_By_UserID(Password& password);
    bool Update_Salt(Password& password);
    bool Update_Hash(Password& password);
    bool Delete(Password& password);
};


#endif //SERVER_PASSWORD_HANDLER_H
