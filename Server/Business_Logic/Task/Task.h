//
// Created by super on 16.11.2023.
//

#ifndef SERVER_TASK_H
#define SERVER_TASK_H

#include <iostream>
#include <winsock2.h>

#include "../../../Tools/Json_Tools.h"

class Task {
public:
    virtual ~Task() = default;
    virtual void Execute() = 0;
};


#endif //SERVER_TASK_H
