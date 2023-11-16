//
// Created by super on 23.11.2023.
//

#include "Registration_Message.h"

IMessage_Builder& Registration_Message::Set_Parametrs() {
    m_parametrs = "registration_data_ans";
    return *this;
}

IMessage_Builder &Registration_Message::Set_Content(std::string& data) {
    m_data = data;
    return *this;
}

std::string Registration_Message::Build_Message() {
    return Pack_Json(m_parametrs,m_data);
}

void Registration_Message::Clear_Message() {
    m_data.clear();
    m_parametrs.clear();
}

void Registration_Message::Validate_Message() {

}