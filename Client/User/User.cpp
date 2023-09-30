//
// Created by super on 30.09.2023.
//

#include "User.h"

bool User::User_Authorization() {
    return false;
}

bool User::User_Registration() {
    bool status;
    std::string registration_data = m_interface->Registration();
    m_server_handler->Write_to_Server("registration_data", registration_data);
    {
        std::unique_lock<std::mutex> lock(m_server_handler->Get_Access_To_Handle_Message_From_Server_Queue_Mutex());
        m_server_handler->Get_Conditional_Variable().wait(lock,[&]{
            auto vector = m_server_handler->Get_Handle_Message_From_Server_Queue();
            for(auto& tmp : vector){
                if(tmp.first == "registration_data_ans"){
                    status = (tmp.second == "true");
                    return true;
                }
            }
            return false;
        });
    }
    return status;
}

User::User(ServerHandler* server_handler):m_server_handler(server_handler) {

}
