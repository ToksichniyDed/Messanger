//
// Created by super on 20.11.2023.
//

#ifndef SERVER_DATABASE_CONNECTOR_H
#define SERVER_DATABASE_CONNECTOR_H

#include <iostream>
#include <libpq-fe.h>
#include <pqxx/pqxx>
#include <memory>

//Класс интерфейс для подключения к базе данных
class IDatabase_Connector {
public:
    virtual ~IDatabase_Connector() = default;

    virtual bool Connect(const std::string &database_name, const std::string &user, const std::string &password,
                         const std::string &host_address, const std::string &port) = 0;

    virtual bool IsConnected() = 0;

    virtual void Disconnect() = 0;

    virtual std::shared_ptr<pqxx::connection> Connector() = 0;
};


//Postgres коннектор
class Database_Connector : public IDatabase_Connector {
private:
    std::shared_ptr<pqxx::connection> m_connection = nullptr;

public:

    bool Connect(const std::string &database_name, const std::string &user, const std::string &password,
                 const std::string &host_address, const std::string &port) override;

    bool IsConnected() override;

    void Disconnect() override;

    std::shared_ptr<pqxx::connection> Connector() override;
};

//Интерфейс фабрики коннекторов
class IDatabase_Connector_Factory {
public:
    IDatabase_Connector_Factory() = default;
    virtual std::shared_ptr<IDatabase_Connector> Create_Connector() = 0;
    virtual ~IDatabase_Connector_Factory() = default;
};


//Фабрика коннекторов postgres
class POSGRES_Database_Connector_Factory : public IDatabase_Connector_Factory {
public:
    std::shared_ptr<IDatabase_Connector> Create_Connector() override {
        return std::make_shared<Database_Connector>();
    }
};

#endif //SERVER_DATABASE_CONNECTOR_H
