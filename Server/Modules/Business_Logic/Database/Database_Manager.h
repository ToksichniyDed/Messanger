//
// Created by super on 22.11.2023.
//

#ifndef SERVER_DATABASE_MANAGER_H
#define SERVER_DATABASE_MANAGER_H

#include "Database_Connector.h"
#include "Query_Executor.h"

// Менеджер для работы с бд. Некая прокладка между запросами и бд

class Database_Manager {
private:
    Database_Connector* m_database_connector;
    Query_Executor* m_query_executor;

public:
    Database_Manager(Database_Connector* database_connector);
    virtual std::vector<std::map<std::string, std::string>> ExecuteCustomSelect(std::string &table_name, const std::string &select_part,
                                                                        const std::string &where_part);
    virtual bool Insert(std::string &table_name, std::vector<std::map<std::string, std::string>> &insert_data);
    virtual bool Update(std::string &table_name, std::vector<std::map<std::string, std::string>> &update_data,
                std::string &primary_key);
    virtual bool Delete(std::string &table_name, std::string &primary_key);
};

#endif //SERVER_DATABASE_MANAGER_H
