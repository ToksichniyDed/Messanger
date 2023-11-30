//
// Created by super on 30.11.2023.
//

#include "Authentication_Data.h"

std::string Authentication_Data::Handle_Authentication_Data(std::string &data) {
    Pack_Json("authentication_data",data);
}

void Authentication_Data::Authentication_Data_Answer() {
    m_cv.Wait(m_mutex.Get_Unique_Lock(),{});

}


