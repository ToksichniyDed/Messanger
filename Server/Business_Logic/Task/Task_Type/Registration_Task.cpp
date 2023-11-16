//
// Created by super on 18.11.2023.
//

#include "Registration_Task.h"

void Registration_Task::Execute() {
    try {
        std::string telephone_number = Unpack_Json("telephone_number", m_data);
        std::string password = Unpack_Json("password", m_data);
        std::cout << "Телефон: " << telephone_number
                  << " Номер: " << password << std::endl;
        std::vector<std::map<std::string,std::string>> vector;
        std::map<std::string,std::string> insert_data;
        insert_data.insert(std::make_pair(telephone_number,password));
        vector.emplace_back(insert_data);
        std::string access = "false";
        std::string user = "user";
        if(m_manager.Insert(user,vector)){
            IMessage_Builder* message_builder = new Registration_Message();
            access = "true";
            std::string message = message_builder->Set_Parametrs().Set_Content(access).Build_Message();
        }
        else
        {
            IMessage_Builder* message_builder = new Registration_Message();
            std::string message = message_builder->Set_Parametrs().Set_Content(access).Build_Message();
        }
    }
    catch (std::exception& Error){
        std::cout<<"Error: "<<Error.what()<<std::endl;
    }
}

Registration_Task::Registration_Task(Client_Socket* socket, std::string &data):m_socket(socket),m_data(data) {

}
