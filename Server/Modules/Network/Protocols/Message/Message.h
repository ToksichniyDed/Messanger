//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>

class Message {
protected:
    std::string m_data;

public:
    explicit Message(std::string data);
    
};


#endif //SERVER_MESSAGE_H
