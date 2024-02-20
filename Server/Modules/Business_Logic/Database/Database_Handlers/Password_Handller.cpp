//
// Created by Toksichniy_Ded on 20.02.2024.
//

#include "Password_Handller.h"

bool Password_Handller::Create(Password &password) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("INSERT INTO Password VALUES ('$1','$2','$3');",
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

Password Password_Handller::Read_By_UserID(Password& password) {
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

bool Password_Handller::Update_Salt(Password &password) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("UPDATE Password SET salt = '$2' WHERE userid = '$1",
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

bool Password_Handller::Delete(Password &password) {
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

bool Password_Handller::Update_Hash(Password &password) {
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
