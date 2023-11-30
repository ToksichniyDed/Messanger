//
// Created by super on 30.11.2023.
//

#ifndef CLIENT_AUTHENTICATION_DATA_H
#define CLIENT_AUTHENTICATION_DATA_H

#include <string>

#include "../../Tools/Json_Tools.h"
#include "../../Tools/Synchronized/Conditional_Variable.h"
#include "../../Tools/Synchronized/Mutex.h"


class Authentication_Data {
private:
    Conditional_Variable m_cv;
    Mutex m_mutex;

public:
    std::string Handle_Authentication_Data(std::string &data);
    void Authentication_Data_Answer();
};


#endif //CLIENT_AUTHENTICATION_DATA_H
