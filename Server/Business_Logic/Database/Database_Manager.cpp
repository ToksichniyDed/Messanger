//
// Created by super on 22.11.2023.
//

#include "Database_Manager.h"

Database_Manager::Database_Manager() {
    m_query_executor = new Query_Executor(&m_database_connector);
}

std::vector<std::map<std::string, std::string>> Database_Manager::ExecuteCustomSelect(std::string &table_name, const std::string &select_part,
                                                                                      const std::string &where_part) {
    return m_query_executor->Execute_Custom_Select(table_name,select_part,where_part);
}

bool Database_Manager::Insert(std::string &table_name, std::vector<std::map<std::string, std::string>> &insert_data) {
    return m_query_executor->Insert(table_name,insert_data);
}

bool Database_Manager::Update(std::string &table_name, std::vector<std::map<std::string, std::string>> &update_data,
                              std::string &primary_key) {
    return m_query_executor->Update(table_name,update_data,primary_key);
}

bool Database_Manager::Delete(std::string &table_name, std::string &primary_key) {
    return m_query_executor->Delete(table_name,primary_key);
}
