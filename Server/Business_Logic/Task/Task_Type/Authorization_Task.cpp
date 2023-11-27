//
// Created by super on 18.11.2023.
//

#include "Authorization_Task.h"

void Authorization_Task::Execute() {
    try{
        std::string telephone_number = Unpack_Json("telephone_number", m_data);
        std::string password = Unpack_Json("password", m_data);
        std::cout << "Телефон: " << telephone_number
                  << " Номер: " << password << std::endl;

        std::vector<std::map<std::string ,std::string >> result_vector = m_manager.ExecuteCustomSelect(
                (std::string &) "User", "user_id, password, salt", "telephone_number = 'telephone_number'");
        if(!result_vector.empty()) {
            for(auto &temp : result_vector){
                auto it = temp.find("salt");
                std::string salt = it->second;
                std::string check_password = Create_Hash_With_Salt(password,salt);
                std::string access = "false";

                IMessage_Builder* message_builder = new Authorization_Message();
                if(!m_manager.ExecuteCustomSelect((std::string &) "User", "user_id, username", "telephone_number = 'telephone_number' AND password = 'check_password'").empty()){
                    access = "true";
                    std::string message = message_builder->Set_Content(access).Set_Parametrs().Build_Message();
                    m_socket->Send_Message(message);
                }
                else{
                    std::string message = message_builder->Set_Content(access).Set_Parametrs().Build_Message();
                    m_socket->Send_Message(message);
                }
            }
        }
    }
    catch (std::exception& Error){
        std::cout<<"Error: "<<Error.what()<<std::endl;

        IMessage_Builder* message_builder = new Authorization_Message();
        std::string access = "error";
        std::string message = message_builder->Set_Content(access).Set_Parametrs().Build_Message();
        m_socket->Send_Message(message);
    }
}

Authorization_Task::Authorization_Task(Client_Socket* socket, std::string &data): m_socket(socket), m_data(data) {
}
