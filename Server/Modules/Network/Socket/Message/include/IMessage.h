//
// Created by Toksichniy_Ded on 20.02.2024.
//

#ifndef SERVER_IMESSAGE_H
#define SERVER_IMESSAGE_H

#include <string>

#include "../../../../Tools/Json_Tools.h"

class IMessage {
public:
    IMessage() = default;
    virtual ~IMessage() = default;
    virtual void Prepare_Data() = 0;
};

#endif //SERVER_IMESSAGE_H
