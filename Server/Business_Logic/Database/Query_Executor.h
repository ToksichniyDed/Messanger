//
// Created by super on 21.11.2023.
//

#ifndef SERVER_QUERY_EXECUTOR_H
#define SERVER_QUERY_EXECUTOR_H

#include <vector>
#include <map>
#include <string>

#include "Database_Connector.h"

class Query_Executor {
private:
    Database_Connector* m_database_connector;

public:
    explicit Query_Executor(Database_Connector* database_connector);
    std::vector<std::map<std::string, std::string>> Execute_Custom_Select(std::string& table_name, const std::string &select_part, const std::string &where_part = "");
    bool Insert(std::string& table_name,std::vector<std::map<std::string, std::string>>& insert_data);
    bool Update(std::string& table_name,std::vector<std::map<std::string, std::string>>& update_data, std::string& primary_key);
    bool Delete(std::string& table_name, std::string& primary_key);

};


#endif //SERVER_QUERY_EXECUTOR_H
