//
// Created by Toksichniy_Ded on 20.02.2024.
//

#include "include/Password_Handler.h"

#include "../../../Tools/OpenSSL_Tools.h"

int Password_Handler::Create(Password &password, pqxx::work& transaction) {
    try{

        password.Set_Salt(Generate_Salt());
        password.Set_Hash(Create_Hash_With_Salt(password.Get_Password(), password.Get_Salt()));

        pqxx::result result = transaction.exec_params(R"(INSERT INTO "Account"."Password" (hash, salt) VALUES ($1,$2) RETURNING passwordid;)",
                                password.Get_Hash(),password.Get_Salt());

        if (result.empty()) {
            throw std::runtime_error("Failed to insert password");
        }

        return result[0][0].as<int>();
    }
    catch (const pqxx::transaction_rollback &e) {
    std::cerr << "Transaction rollback Password_Handler::Create(): " << e.what() << std::endl;
        return -1;
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error Password_Handler::Create(): " << e.what() << std::endl;
        return -1;
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed Password_Handler::Create(): " << e.what() << std::endl;
        return -1;
    } catch (const std::exception &e) {
        std::cerr << "Error Password_Handler::Create(): " << e.what() << std::endl;
        return -1;
    }
}

bool Password_Handler::Update_Salt(Password &password, User& user) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("UPDATE \"Password\" SET salt = $2 WHERE userid = $1;",
                                std::to_string(user.Get_UserID()),password.Get_Salt());

        return true;
    }
    catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback Password_Handler::Update_Salt(): " << e.what() << std::endl;
        return false;
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error Password_Handler::Update_Salt(): " << e.what() << std::endl;
        return false;
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed Password_Handler::Update_Salt(): " << e.what() << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "Error Password_Handler::Update_Salt(): " << e.what() << std::endl;
        return false;
    }
}

bool Password_Handler::Delete(Password &password, User& user) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("DELETE FROM \"Password\" WHERE userid = $1;",
                                std::to_string(user.Get_UserID()));

        transaction.commit();
        return true;
    }
    catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback Password_Handler::Delete(): " << e.what() << std::endl;
        return false;
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error Password_Handler::Delete(): " << e.what() << std::endl;
        return false;
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed Password_Handler::Delete(): " << e.what() << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "Error Password_Handler::Delete(): " << e.what() << std::endl;
        return false;
    }
}

bool Password_Handler::Update_Hash(Password &password, User& user) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        transaction.exec_params("UPDATE \"Password\" SET hash = $2 WHERE userid = $1;",
                                std::to_string(user.Get_UserID()),password.Get_Hash());

        return true;
    }
    catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback Password_Handler::Update_Hash(): " << e.what() << std::endl;
        return false;
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error Password_Handler::Update_Hash(): " << e.what() << std::endl;
        return false;
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed Password_Handler::Update_Hash(): " << e.what() << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "Error Password_Handler::Update_Hash(): " << e.what() << std::endl;
        return false;
    }
}

void Password_Handler::Set_Connector(std::shared_ptr<IDatabase_Connector> connector) {
    m_connector = std::move(connector);
}

void Password_Handler::Disconnect_Connector() {
    m_connector = nullptr;
}

Password_Handler::Password_Handler() {
}

Password Password_Handler::Read_By_PasswordID(int passwordid) {
    try{
        pqxx::work transaction(*m_connector->Connector());

        pqxx::result query_result = transaction.exec_params("SELECT * FROM \"Password\" WHERE userid = $1;",
                                std::to_string(passwordid));

        transaction.commit();
        return std::move(m_mapper->Mapping(query_result));
    }
    catch (const pqxx::transaction_rollback &e) {
        std::cerr << "Transaction rollback Password_Handler::Read_By_PasswordID(): " << e.what() << std::endl;
        return std::move(*new Password());
    } catch (const pqxx::sql_error &e) {
        std::cerr << "SQL-error Password_Handler::Read_By_PasswordID(): " << e.what() << std::endl;
        return std::move(*new Password());
    } catch (const pqxx::broken_connection &e) {
        std::cerr << "Connection failed Password_Handler::Read_By_PasswordID(): " << e.what() << std::endl;
        return std::move(*new Password());
    } catch (const std::exception &e) {
        std::cerr << "Error Password_Handler::Read_By_PasswordID(): " << e.what() << std::endl;
        return std::move(*new Password());
    }
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
