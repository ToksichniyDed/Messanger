//
// Created by super on 20.11.2023.
//

#ifndef SERVER_DATABASE_CONNECTOR_H
#define SERVER_DATABASE_CONNECTOR_H

#include <iostream>
#include <libpq-fe.h>

class Database_Connector {
private:
    PGconn *m_connector = nullptr;

public:
    ~Database_Connector();
    bool Connect(const std::string &database_name, const std::string &user, const std::string &password,
                 const std::string &host_address, const std::string &port);
    bool IsConnected();
    void Disconnect();
    PGconn* Get_PGcon();
};


#endif //SERVER_DATABASE_CONNECTOR_H
