//
// Created by super on 20.11.2023.
//

#include "Database_Connector.h"

Database_Connector::~Database_Connector() {
    if(m_connector)
        PQfinish(m_connector);
}

// Подключение по указанным данным
bool Database_Connector::Connect(const std::string &database_name, const std::string &user, const std::string &password,
                                 const std::string &host_address, const std::string &port) {
    std::string connection_Str = "dbname=" + database_name + " user=" + user + " password=" + password +
                                " hostaddr=" + host_address + " port=" + port;
    m_connector = PQconnectdb(connection_Str.c_str());
    return IsConnected();
}

void Database_Connector::Disconnect() {
    if(m_connector) {
        PQfinish(m_connector);
        m_connector = nullptr;
    }
}

// Проверка соединения
bool Database_Connector::IsConnected() {
    return (m_connector != nullptr && PQstatus(m_connector) == CONNECTION_OK);
}

PGconn *Database_Connector::Get_PGcon() {
    return m_connector;
}
