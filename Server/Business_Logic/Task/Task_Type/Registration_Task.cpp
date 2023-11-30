//
// Created by super on 18.11.2023.
//

#include "Registration_Task.h"

//Распаковка оправленных данных. С помощью OpenSSL_Tools пароль+соль хэшируется, после чего создается запрос
// (с помощью класса Query_Executor) в базу данных на добавление нового пользователя.
// В базу добавляется номер телефона, соль и  хэшированный пароль. В соответствии с результатом создается ответное сообщение с помощью билдера.
//Так как строка хэшируется, то можно не опасаться SQL-инъекции.
void Registration_Task::Execute() {
    try {
        std::string telephone_number = Unpack_Json("telephone_number", m_data);
        std::string password = Unpack_Json("password", m_data);
        std::vector<std::map<std::string,std::string>> vector;
        std::map<std::string,std::string> insert_data;

        std::cout << "Телефон: " << telephone_number
                  << " Номер: " << password << std::endl;

        insert_data.insert(std::make_pair("telephone_number",telephone_number));
        std::string salt = Generate_Salt();
        insert_data.insert(std::make_pair("password", Create_Hash_With_Salt(password,salt)));
        insert_data.insert(std::make_pair("salt", salt));
        vector.emplace_back(insert_data);
        std::string access = "false";
        std::string user = "user";
        IMessage_Builder* message_builder = new Registration_Message();

        if(m_manager.Insert(user,vector)){
            access = "true";
            std::string message = message_builder->Set_Parametrs().Set_Content(access).Build_Message();
        }
        else
        {
            std::string message = message_builder->Set_Parametrs().Set_Content(access).Build_Message();
            m_socket->Send_Message(message);
        }
    }

    catch (std::exception& Error){
        std::cout<<"Error: "<<Error.what()<<std::endl;
    }
}

Registration_Task::Registration_Task(Client_Socket* socket, std::string &data): m_socket(socket), m_data(data) {

}
