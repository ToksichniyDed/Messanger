//
// Created by Toksichniy_Ded on 28.02.2024.
//

#ifndef SERVER_IMESSAGE_CREATOR_H
#define SERVER_IMESSAGE_CREATOR_H

#include <memory>
#include "IMessage.h"


class IMessage_Creator {
public:
    //std::string& data
    virtual std::unique_ptr<IMessage> Create_Message(std::string& data) = 0;
    virtual ~IMessage_Creator() = default;
};


#endif //SERVER_IMESSAGE_CREATOR_H
