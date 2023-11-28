//
// Created by super on 13.11.2023.
//

#ifndef SERVER_CONDITIONAL_VARIABLE_H
#define SERVER_CONDITIONAL_VARIABLE_H

#include <condition_variable>
#include <functional>

class Conditional_Variable {
private:
    std::condition_variable m_cv;

public:
    Conditional_Variable &Wait(std::unique_lock<std::mutex> lock, std::function<bool()> condition);
    Conditional_Variable &Notify_One();
    Conditional_Variable &Notify_All();
};


#endif //SERVER_CONDITIONAL_VARIABLE_H
