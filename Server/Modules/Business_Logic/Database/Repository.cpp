//
// Created by Toksichniy_Ded on 20.02.2024.
//

#include "Repository.h"

bool Repository::User_Registration(std::shared_ptr<IDatabase_Connector> connector, std::shared_ptr<User> user,  std::shared_ptr<Password> password) {
    m_user_handler->Set_Connector(connector);

    pqxx::work transaction(*connector->Connector());

    auto passwordid = m_password_handler->Create(*password, transaction);

    if(passwordid<0)
        return false;

    if(!m_user_handler->Create_User(*user,passwordid, transaction))
        return false;

    m_user_handler->Disconnect_Connector();

    transaction.commit();
    return true;
}

bool Repository::User_Authorization(std::shared_ptr<IDatabase_Connector> connector, std::shared_ptr<User> user,  std::shared_ptr<Password> password) {
    //Здесь пытаемся найти пользователя по номеру или никнейму, смотря что есть в user
    m_user_handler->Set_Connector(connector);

    User db_user;
    if(!user->Get_Telephone_Number().empty())//Попытка найти по номеру
        db_user = std::move(m_user_handler->Read_User_By_Telephone_Number(*user));

    if(!user->Get_UserName().empty())//Попытка найти по никнейму
        db_user = std::move(m_user_handler->Read_User_By_UserName(*user));

    m_user_handler->Disconnect_Connector();

    m_password_handler->Set_Connector(connector);
    auto db_password = m_password_handler->Read_By_PasswordID(db_user.Get_Password_Id());
    m_password_handler->Disconnect_Connector();

    if(db_password.Get_Hash() == Create_Hash_With_Salt(password->Get_Password(), db_password.Get_Hash()))
        return true;
    return false;
}

Repository::Repository(std::unique_ptr<User_Handler> u_handler, std::unique_ptr<Password_Handler> p_handler){
    if(u_handler)
        m_user_handler = std::move(u_handler);

    if(p_handler)
        m_password_handler=std::move(p_handler);

    if(!(m_user_handler && m_password_handler))
        throw std::runtime_error("Failed create Repository!");
}
