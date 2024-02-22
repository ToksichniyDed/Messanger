//
// Created by Toksichniy_Ded on 22.02.2024.
//

#include "include/Registration_Message.h"

void Registration_Message::Prepare_Data() {
    m_user = new User();
    m_user->Set_UserName(Unpack_Json("username", m_data));
    m_user->Set_Telephone_Number(Unpack_Json("telephone_number", m_data));
}

User *Registration_Message::Get_User() {
    return m_user;
}
