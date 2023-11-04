//
// Created by super on 30.09.2023.
//

#include "User.h"

bool User::User_Registration_Authorization(std::string type) {
    bool status;
    std::string registration_data = m_interface->Registration_Authorization();
    m_mediator->Set_Data_To_ServerHandler_From_User(type, registration_data);
    std::string ans = "_ans";
    type.append(ans);
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    m_mediator->Get_CV_To_Once_Used().wait(lock,[&]{std::string temp = m_mediator->Get_Once_Used_Data_To_User_From_ServerHandler(type);
        if(temp.empty())
            return false;
        status = (temp == "true");
        return true;});
    return status;
}

void User::Set_Mediator(User_ServerHandler_Mediator *mediator) {
    m_mediator=mediator;
}

