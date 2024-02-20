//
// Created by super on 20.11.2023.
//

#ifndef SERVER_DATABASE_CONNECTOR_H
#define SERVER_DATABASE_CONNECTOR_H

#include <iostream>
#include <libpq-fe.h>
#include <pqxx/pqxx>

//Класс для подключения к базе данных

class IDatabase_Connector {
public:
    virtual ~IDatabase_Connector() = default;

    virtual bool Connect(const std::string &database_name, const std::string &user, const std::string &password,
                         const std::string &host_address, const std::string &port) = 0;

    virtual bool IsConnected() = 0;

    virtual void Disconnect() = 0;

    virtual pqxx::connection* Connector() = 0;
};

class Database_Connector : public IDatabase_Connector {
private:
    pqxx::connection *m_connection;

public:
    ~Database_Connector() override;

    bool Connect(const std::string &database_name, const std::string &user, const std::string &password,
                 const std::string &host_address, const std::string &port) override;

    bool IsConnected() override;

    void Disconnect() override;

    pqxx::connection *Connector() override;
};

class IDatabase_Connector_Factory {
public:
    virtual IDatabase_Connector *Create_Connector() = 0;

    virtual ~IDatabase_Connector_Factory() = default;
};

class POSGRES_Database_Connector_Factory : public IDatabase_Connector_Factory {
public:
    IDatabase_Connector *Create_Connector() override {
        return new Database_Connector();
    }
};

#endif //SERVER_DATABASE_CONNECTOR_H
