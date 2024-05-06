//
// Created by Toksichniy_Ded on 09.03.2024.
//

#include "Server_Error_Protocol.h"

std::string Server_Error_Protocol::Build_Message() {
    return Pack_Json(m_parametrs,m_data);;
}

IMessage_Builder &Server_Error_Protocol::Set_Parametrs() {
    m_parametrs = "error_on_server_ans";
    return *this;
}

IMessage_Builder &Server_Error_Protocol::Set_Content(std::string data) {
    m_data = std::move(data);
    return *this;
}

void Server_Error_Protocol::Clear_Message() {
    m_data.clear();
    m_parametrs.clear();
}
