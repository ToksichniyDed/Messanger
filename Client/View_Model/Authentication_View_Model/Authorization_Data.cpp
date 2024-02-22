//
// Created by super on 30.11.2023.
//

#include "Authentication_Data.h"

std::string Authorization_Data::Handle_Authorization_Data(std::string &data) {
    Pack_Json("authorization_data", data);
}

void Authorization_Data::Authorization_Data_Answer() {
    m_cv.Wait(m_mutex.Get_Unique_Lock(),{});

}


