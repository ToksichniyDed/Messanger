//
// Created by super on 13.11.2023.
//

#include "Conditional_Variable.h"

//Второй аргумент может быть заменнен дефолтным значением, потому что иногда мы ждем только уведомление
void Conditional_Variable::Wait(std::unique_lock<std::mutex>& lock, std::function<bool()> condition) {
    m_cv.wait(lock, std::move(condition));
}

void Conditional_Variable::Notify_One() {
    m_cv.notify_one();
}

void Conditional_Variable::Notify_All() {
    m_cv.notify_all();
}

