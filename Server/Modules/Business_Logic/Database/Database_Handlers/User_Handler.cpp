//
// Created by Toksichniy_Ded on 20.02.2024.
//

#include <utility>

#include "include/User_Handler.h"

bool User_Handler::Create_User(User& new_user) {
    try {
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("INSERT INTO \"User\" (username, telephonenumber) VALUES ($1,$2);", new_user.Get_UserName().c_str(),
                                                            new_user.Get_Telephone_Number().c_str());

        transaction.commit();

        return true;
    } catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback: " << e.what() << std::endl;
        return false;
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error: " << e.what() << std::endl;
        return false;
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

User User_Handler::Read_User_By_Telephone_Number(User& user) {
    try {
        pqxx::work transaction(*m_connector->Connector());

        pqxx::result query_result = transaction.exec_params("SELECT * FROM \"User\" WHERE telephonenumber = $1;",
                                                            user.Get_Telephone_Number());

        transaction.commit();

        return std::move(m_mapper->Mapping(query_result));
    } catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback: " << e.what() << std::endl;
        return std::move(*new User());
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error: " << e.what() << std::endl;
        return std::move(*new User());
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return std::move(*new User());
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return std::move(*new User());
    }
}

bool User_Handler::Update_UserName(User &user) {
    try {
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("UPDATE \"User\" Set UserName = $1 WHERE UserID = $2;",
                                user.Get_UserName(), std::to_string(user.Get_UserID()));

        transaction.commit();
        return true;
    } catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback: " << e.what() << std::endl;
        return false;
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error: " << e.what() << std::endl;
        return false;
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

bool User_Handler::Delete_User(User &user) {
    try {
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("DELETE FROM \"User\" WHERE UserID = $1;", std::to_string(user.Get_UserID()));

        transaction.commit();

        return true;
    } catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback: " << e.what() << std::endl;
        return false;
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error: " << e.what() << std::endl;
        return false;
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

User User_Handler::Read_User_By_UserName(User& user) {
    try {
        pqxx::work transaction(*m_connector->Connector());

        pqxx::result query_result = transaction.exec_params("SELECT * FROM \"User\" WHERE username = $1;",
                                                            (user.Get_UserName()));

        transaction.commit();

        return std::move(m_mapper->Mapping(query_result));
    } catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback: " << e.what() << std::endl;
        return std::move(*new User());
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error: " << e.what() << std::endl;
        return std::move(*new User());
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return std::move(*new User());
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return std::move(*new User());
    }
}

User_Handler::User_Handler(std::shared_ptr<IDatabase_Connector> connector, std::unique_ptr<UserMapper> mapper){
    if(connector)
        m_connector = connector;

    if(mapper)
        m_mapper = std::move(mapper);

    if(!(m_connector && m_mapper))
        throw std::runtime_error("Failed create User_Handler!");
}

void User_Handler::Set_Connector(std::shared_ptr<IDatabase_Connector> connector) {
    m_connector = std::move(connector);
}

void User_Handler::Disconnect_Connector() {
    m_connector = nullptr;
}
