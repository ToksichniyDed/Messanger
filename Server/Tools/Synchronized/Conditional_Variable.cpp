//
// Created by super on 13.11.2023.
//

#include "Conditional_Variable.h"

Conditional_Variable &Conditional_Variable::Wait(std::unique_lock<std::mutex> lock, std::function<bool()> condition = [] { return true; }) {
    m_cv.wait(lock, std::move(condition));
    return *this;
}

Conditional_Variable &Conditional_Variable::Notify_One() {
    m_cv.notify_one();
    return *this;
}

Conditional_Variable &Conditional_Variable::Notify_All() {
    m_cv.notify_all();
    return *this;
}

