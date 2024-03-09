//
// Created by super on 20.11.2023.
//

#include "Database_Connector.h"

// Подключение по указанным данным
bool Database_Connector::Connect(const std::string &database_name, const std::string &user, const std::string &password,
                                 const std::string &host_address, const std::string &port) {
    std::string connection_Str = "dbname=" + database_name + " user=" + user + " password=" + password +
                                " hostaddr=" + host_address + " port=" + port;
    m_connection =  std::make_shared<pqxx::connection>(connection_Str);
    return IsConnected();
}

void Database_Connector::Disconnect() {
   m_connection->close();
}

// Проверка соединения
bool Database_Connector::IsConnected() {
    return m_connection->is_open();
}

std::shared_ptr<pqxx::connection> Database_Connector::Connector() {
    return m_connection;
}

