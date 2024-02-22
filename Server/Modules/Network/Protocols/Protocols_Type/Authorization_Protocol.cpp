//
// Created by super on 23.11.2023.
//

#include "Authorization_Protocol.h"

IMessage_Builder& Authorization_Protocol::Set_Parametrs() {
    m_parametrs = "authorization_data_ans";
    return *this;
}

IMessage_Builder &Authorization_Protocol::Set_Content(std::string& data) {
    m_data = data;
    return *this;
}

std::string Authorization_Protocol::Build_Message() {
    return Pack_Json(m_parametrs,m_data);
}

void Authorization_Protocol::Clear_Message() {
    m_data.clear();
    m_parametrs.clear();
}

