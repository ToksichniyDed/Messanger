//
// Created by super on 23.11.2023.
//

#include "Authorization_Message.h"

IMessage_Builder& Authorization_Message::Set_Parametrs() {
    m_parametrs = "authorization_data_ans";
    return *this;
}

IMessage_Builder &Authorization_Message::Set_Content(std::string& data) {
    m_data = data;
    return *this;
}

std::string Authorization_Message::Build_Message() {
    return Pack_Json(m_parametrs,m_data);
}

void Authorization_Message::Clear_Message() {
    m_data.clear();
    m_parametrs.clear();
}

void Authorization_Message::Validate_Message() {

}


