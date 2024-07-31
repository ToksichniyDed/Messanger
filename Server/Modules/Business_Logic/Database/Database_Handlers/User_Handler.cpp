//
// Created by Toksichniy_Ded on 20.02.2024.
//
#include "include/User_Handler.h"

bool User_Handler::Create_User(const User &new_user, int passwordid, pqxx::work &transaction) {
    try {
        std::string username = Generate_Random_Username();

        //Проверка на уникальный username в БД
        {
            User temp_user;
            auto temp_username = username;
            temp_user.Set_UserName(temp_username);
            while (*(new User) != Read_User_By_UserName(temp_user, &transaction)) {
                temp_username = Generate_Random_Username();
                username = temp_username;
                temp_user.Set_UserName(temp_username);
            }
        }

        transaction.exec_params(
            R"(INSERT INTO "Account"."User" (username, telephonenumber, passwordid) VALUES ($1,$2,$3);)",
            username.c_str(),
            new_user.Get_Telephone_Number().c_str(), std::to_string(passwordid));

        return true;
    } catch (const std::exception &Error) {
        std::cerr << "Error User_Handler::Create_User(): " << Error.what() << std::endl;
        return false;
    }
}

User User_Handler::Read_User_By_Telephone_Number(const User &user, pqxx::work *transaction) {
    bool own_transaction = false;
    if (!transaction) {
        own_transaction = true;
        transaction = new pqxx::work(*m_connector->Connector());
    }

    try {
        pqxx::result query_result = transaction->exec_params(
            R"(SELECT * FROM "Account"."User" WHERE telephonenumber = $1;)",
            user.Get_Telephone_Number()
        );

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
        std::cerr << "Error User_Handler::Read_User_By_Telephone_Number(): " << Error.what() << std::endl;
        return std::move(*new User());
    }
}


bool User_Handler::Update_UserName(const User& user, pqxx::work* transaction) {
    bool own_transaction = false;
    if (!transaction) {
        own_transaction = true;
        transaction = new pqxx::work(*m_connector->Connector());
    }

    try {
        transaction->exec_params(
            R"(UPDATE "Account"."User" SET username = $1 WHERE userid = $2;)",
            user.Get_UserName(), user.Get_UserID()
        );

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
        std::cerr << "Error User_Handler::Update_UserName(): " << Error.what() << std::endl;
        return false;
    }
}


bool User_Handler::Delete_User(const User& user, pqxx::work* transaction) {
    bool own_transaction = false;
    if (!transaction) {
        own_transaction = true;
        transaction = new pqxx::work(*m_connector->Connector());
    }

    try {
        transaction->exec_params(
            R"(DELETE FROM "Account"."User" WHERE userid = $1;)",
            user.Get_UserID()
        );

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
        std::cerr << "Error User_Handler::Delete_User(): " << Error.what() << std::endl;
        return false;
    }
}


User User_Handler::Read_User_By_UserName(const User& user, pqxx::work* transaction) {
    bool own_transaction = false;
    if (!transaction) {
        own_transaction = true;
        transaction = new pqxx::work(*m_connector->Connector());
    }

    try {
        pqxx::result query_result = transaction->exec_params(
            R"(SELECT * FROM "Account"."User" WHERE username = $1;)",
            user.Get_UserName()
        );

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
        std::cerr << "Error User_Handler::Read_User_By_UserName(): " << Error.what() << std::endl;
        return std::move(*new User());
    }
}


std::string User_Handler::Generate_Random_Username(int length) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    std::string username;
    std::generate_n(std::back_inserter(username), length, [&]() { return chars[dist(generator)]; });

    return username;
}

User_Handler::User_Handler(std::shared_ptr<IDatabase_Connector> connector, std::unique_ptr<UserMapper> mapper) {
    if (connector)
        m_connector = connector;

    if (mapper)
        m_mapper = std::move(mapper);

    if (!(m_connector && m_mapper))
        throw std::runtime_error("Failed create User_Handler!");
}

void User_Handler::Set_Connector(std::shared_ptr<IDatabase_Connector> connector) {
    m_connector = std::move(connector);
}

void User_Handler::Disconnect_Connector() {
    m_connector = nullptr;
}
