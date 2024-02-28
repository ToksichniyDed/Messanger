//
// Created by Toksichniy_Ded on 28.02.2024.
//

#ifndef SERVER_IMESSAGE_CREATOR_H
#define SERVER_IMESSAGE_CREATOR_H

#include "IMessage.h"


class IMessage_Creator {
public:
    //std::string& data
    virtual IMessage* Create_Message(std::string& data) = 0;
};


#endif //SERVER_IMESSAGE_CREATOR_H
