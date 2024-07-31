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
    catch (const std::exception &Error) {
        std::cerr << "Error Password_Handler::Create(): " << Error.what() << std::endl;
        return -1;
    }
}

bool Password_Handler::Update_Salt(Password &password, User &user, pqxx::work *transaction) {
    bool own_transaction = false;
    if (!transaction) {
        own_transaction = true;
        transaction = new pqxx::work(*m_connector->Connector());
    }

    try {
        transaction->exec_params(R"(UPDATE "Account"."Password" SET salt = $2 WHERE userid = $1;)",
                                 user.Get_UserID(), password.Get_Salt());

        if (own_transaction) {
            transaction->commit();
            delete transaction;
        }

        return true;
    } catch (const std::exception &Error) {
        transaction->abort();
        if (own_transaction) {
            delete transaction;
        }
        std::cerr << "Error Password_Handler::Update_Salt(): " << Error.what() << std::endl;
        return false;
    }
}


bool Password_Handler::Update_Hash(Password &password, User &user, pqxx::work *transaction) {
    bool own_transaction = false;
    if (!transaction) {
        own_transaction = true;
        transaction = new pqxx::work(*m_connector->Connector());
    }

    try {
        transaction->exec_params(R"(UPDATE "Account"."Password" SET hash = $2 WHERE userid = $1;)",
                                 user.Get_UserID(), password.Get_Hash());

        if (own_transaction) {
            transaction->commit();
            delete transaction;
        }

        return true;
    } catch (const std::exception &Error) {
        transaction->abort();
        if (own_transaction) {
            delete transaction;
        }
        std::cerr << "Error Password_Handler::Update_Hash(): " << Error.what() << std::endl;
        return false;
    }
}


bool Password_Handler::Delete(Password &password, User &user, pqxx::work *transaction) {
    bool own_transaction = false;
    if (!transaction) {
        own_transaction = true;
        transaction = new pqxx::work(*m_connector->Connector());
    }

    try {
        transaction->exec_params(R"(DELETE FROM "Account"."Password" WHERE userid = $1;)", user.Get_UserID());

        if (own_transaction) {
            transaction->commit();
            delete transaction;
        }

        return true;
    } catch (const std::exception &Error) {
        transaction->abort();
        if (own_transaction) {
            delete transaction;
        }
        std::cerr << "Error Password_Handler::Delete(): " << Error.what() << std::endl;
        return false;
    }
}



Password Password_Handler::Read_By_PasswordID(int passwordid, pqxx::work *transaction) {
    bool own_transaction = false;
    if (!transaction) {
        own_transaction = true;
        transaction = new pqxx::work(*m_connector->Connector());
    }

    try {
        pqxx::result query_result = transaction->exec_params(R"(SELECT * FROM "Account"."Password" WHERE passwordid = $1;)",
                                                             passwordid);

        if (own_transaction) {
            transaction->commit();
            delete transaction;
        }

        return std::move(m_mapper->Mapping(query_result));
    } catch (const std::exception &Error) {
        transaction->abort();
        if (own_transaction) {
            delete transaction;
        }
        std::cerr << "Error Password_Handler::Read_By_PasswordID(): " << Error.what() << std::endl;
        return std::move(*new Password());
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
