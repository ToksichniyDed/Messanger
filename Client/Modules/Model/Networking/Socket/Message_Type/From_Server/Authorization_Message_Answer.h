//
// Created by Toksichniy_Ded on 01.04.2024.
//

#ifndef CLIENT_AUTHORIZATION_MESSAGE_ANSWER_H
#define CLIENT_AUTHORIZATION_MESSAGE_ANSWER_H

#include <string>

#include "../../../../../Tools/Json_Tools.h"
#include "../IMessage.h"

class Authorization_Message_Answer:IMessage {
protected:
    std::string m_data;
    bool m_status;

public:
    void Prepare_Data() override;
    [[nodiscard]] bool Get_Authorization_Status() const;
};

void Authorization_Message_Answer::Prepare_Data() {
    try{
        m_status = (Unpack_Json("data",m_data) == "true");
    }
    catch(std::exception& Error) {
        std::cout<<Error.what()<<std::endl;
    }
}

bool Authorization_Message_Answer::Get_Authorization_Status() const {
    return m_status;
}


#endif //CLIENT_AUTHORIZATION_MESSAGE_ANSWER_H
