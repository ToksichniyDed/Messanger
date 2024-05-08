//
// Created by Toksichniy_Ded on 20.02.2024.
//

#include "Repository.h"

bool Repository::User_Registration(std::shared_ptr<IDatabase_Connector> connector, std::shared_ptr<User> user,  std::shared_ptr<Password> password) {
    m_user_handler->Set_Connector(connector);

    if(!m_user_handler->Create_User(*user))
        return false;

    password->Set_Salt(Generate_Salt());
    password->Set_Hash(Create_Hash_With_Salt(password->Get_Password(),password->Get_Salt()));

    User db_user = m_user_handler->Read_User_By_UserName(*user);
    m_user_handler->Disconnect_Connector();

    m_password_handler->Set_Connector(connector);
    password->Set_UserID(db_user.Get_UserID());

    if(!m_password_handler->Create(*password)){
        m_password_handler->Disconnect_Connector();
        m_user_handler->Set_Connector(connector);
        m_user_handler->Delete_User(db_user);
        m_user_handler->Disconnect_Connector();
        return false;
    }

    m_password_handler->Disconnect_Connector();

    return true;
}

bool Repository::User_Authorization(std::shared_ptr<IDatabase_Connector> connector, std::shared_ptr<User> user,  std::shared_ptr<Password> password) {
    m_user_handler->Set_Connector(connector);

    User db_user;
    if(!user->Get_Telephone_Number().empty())
        db_user = std::move(m_user_handler->Read_User_By_Telephone_Number(*user));

    if(!user->Get_UserName().empty())
        db_user = std::move(m_user_handler->Read_User_By_UserName(*user));

    m_user_handler->Disconnect_Connector();
    m_password_handler->Set_Connector(connector);

    Password db_password = m_password_handler->Read_By_UserID(*password);

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
