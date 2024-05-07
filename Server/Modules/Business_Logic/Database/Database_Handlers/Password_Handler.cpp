//
// Created by Toksichniy_Ded on 20.02.2024.
//

#include "include/Password_Handler.h"

bool Password_Handler::Create(Password &password) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("INSERT INTO Password (userid, hash, salt) VALUES ('$1','$2','$3');",
                                (password.Get_UserID(),password.Get_Hash(),password.Get_Salt()));

        transaction.commit();

        return true;
    }
    catch (const pqxx::transaction_rollback &e) {
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

Password Password_Handler::Read_By_UserID(Password& password) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        pqxx::result query_result = transaction.exec_params("SELECT * FROM Password WHERE userid = '$1",
                                                            std::to_string(password.Get_UserID()));

        transaction.commit();
    }
    catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback: " << e.what() << std::endl;
        return std::move(*new Password());
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error: " << e.what() << std::endl;
        return std::move(*new Password());
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return std::move(*new Password());
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return std::move(*new Password());
    }
}

bool Password_Handler::Update_Salt(Password &password) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("UPDATE Password SET salt = '$2' WHERE userid = '$1';",
                                (std::to_string(password.Get_UserID()),password.Get_Salt()));

        return true;
    }
    catch (const pqxx::transaction_rollback &e) {
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

bool Password_Handler::Delete(Password &password) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("DELETE FROM Password WHERE userid = '$1';",
                                std::to_string(password.Get_UserID()));

        transaction.commit();
        return true;
    }
    catch (const pqxx::transaction_rollback &e) {
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

bool Password_Handler::Update_Hash(Password &password) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("UPDATE Password SET hash = '$2' WHERE userid = '$1",
                                (std::to_string(password.Get_UserID()),password.Get_Hash()));

        return true;
    }
    catch (const pqxx::transaction_rollback &e) {
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

void Password_Handler::Set_Connector(std::shared_ptr<IDatabase_Connector> connector) {
    m_connector = std::move(connector);
}

void Password_Handler::Disconnect_Connector() {
    m_connector = nullptr;
}

Password_Handler::Password_Handler(std::shared_ptr<IDatabase_Connector> connector,
                                   std::unique_ptr<PasswordMapper> mapper) {
    if(connector)
        m_connector = connector;

    if(mapper)
        m_mapper = std::move(mapper);

    if(!(m_connector && m_mapper))
        throw std::runtime_error("Failed create Password_Handler!");
}
