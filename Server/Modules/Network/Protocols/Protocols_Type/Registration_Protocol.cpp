//
// Created by super on 23.11.2023.
//

#include "Registration_Protocol.h"

IMessage_Builder& Registration_Protocol::Set_Parametrs() {
    m_parametrs = "registration_data_ans";
    return *this;
}

IMessage_Builder &Registration_Protocol::Set_Content(std::string data) {
    m_data = data;
    return *this;
}

std::string Registration_Protocol::Build_Message() {
    return Pack_Json(m_parametrs,m_data);
}

void Registration_Protocol::Clear_Message() {
    m_data.clear();
    m_parametrs.clear();
}
