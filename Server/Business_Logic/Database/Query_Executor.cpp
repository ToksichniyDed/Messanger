//
// Created by super on 21.11.2023.
//

#include "Query_Executor.h"

Query_Executor::Query_Executor(Database_Connector *database_connector):m_database_connector(database_connector) {
}

//Запрос с выборкой по указанным select и where частям. Представлена дефолтный запрос без where части.
//Возвращается вектор мап,т.к значений по where части может быть несколько. Мапа для названия столбца - значения.
std::vector<std::map<std::string, std::string>>
Query_Executor::Execute_Custom_Select(std::string &table_name, const std::string &select_part,
                                      const std::string &where_part) {
    std::string query = "SELECT " + select_part + " FROM " + table_name;
    if (!where_part.empty()) {
        query += " WHERE " + where_part;
    }

    PGresult* query_result = PQexec(m_database_connector->Get_PGcon(), query.c_str());
    if(PQresultStatus(query_result) != PGRES_TUPLES_OK){
        std::cout << "Query execution failed: " << PQerrorMessage(m_database_connector->Get_PGcon()) << std::endl;
        PQclear(query_result);
    }

    int num_rows = PQntuples(query_result);
    int num_cols = PQnfields(query_result);

    std::vector<std::map<std::string, std::string>> result;

    for(int i = 0; i<num_rows;++i){
        std::map<std::string, std::string> row;
        for(int j = 0; j<num_cols;++j)
        {
            std::string col_name = PQfname(query_result, j);
            std::string col_value = PQgetvalue(query_result, i, j);
            row[col_name] = col_value;
        }
        result.push_back(row);
    }

    return result;
}


bool Query_Executor::Insert(std::string &table_name, std::vector<std::map<std::string, std::string>> &insert_data) {
    std::string query = "INSERT INTO " + table_name + " (";

    // Формируем список столбцов для вставки
    for (const auto& column : insert_data.front()) {
        query += column.first + ",";
    }
    query.pop_back();

    query += ") VALUES ";

    for (const auto& row : insert_data) {
        query += "(";
        for (const auto& column : row) {
            query += "'" + column.second + "',";
        }
        query.pop_back();
        query += "),";
    }
    query.pop_back();

    PGresult* query_result = PQexec(m_database_connector->Get_PGcon(), query.c_str());
    if(PQresultStatus(query_result) != PGRES_TUPLES_OK){
        std::cout << "Query execution failed: " << PQerrorMessage(m_database_connector->Get_PGcon()) << std::endl;
        PQclear(query_result);
        return false;
    }

    return true;
}


bool Query_Executor::Update(std::string &table_name, std::vector<std::map<std::string, std::string>> &update_data,
                            std::string &primary_key) {
    std::string query = "UPDATE " + table_name + " SET ";

    for (const auto &data : update_data) {
        for (const auto &entry : data) {
            query += entry.first + " = '" + entry.second + "', ";
        }
    }

    query.pop_back();
    query.pop_back();

    query += " WHERE primary_key_column = '" + primary_key + "';";

    PGresult* query_result = PQexec(m_database_connector->Get_PGcon(), query.c_str());
    if(PQresultStatus(query_result) != PGRES_TUPLES_OK){
        std::cout << "Query execution failed: " << PQerrorMessage(m_database_connector->Get_PGcon()) << std::endl;
        PQclear(query_result);
        return false;
    }
    return true;
}


bool Query_Executor::Delete(std::string &table_name, std::string &primary_key) {
    std::string query = "DELETE FROM " + table_name + " WHERE primary_key_column = '" + primary_key + "';";
    PGresult* query_result = PQexec(m_database_connector->Get_PGcon(), query.c_str());
    if(PQresultStatus(query_result) != PGRES_TUPLES_OK){
        std::cout << "Query execution failed: " << PQerrorMessage(m_database_connector->Get_PGcon()) << std::endl;
        PQclear(query_result);
        return false;
    }
    return true;
}



