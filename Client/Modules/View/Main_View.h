//
// Created by Toksichniy_Ded on 09.04.2024.
//

#ifndef CLIENT_MAIN_VIEW_H
#define CLIENT_MAIN_VIEW_H

#include <memory>
#include <iostream>
#include <cstdio>

#include <../../View_Model/Enter_View_Model/Registration_View_Model.h>


class Main_View {
public:
    using Registration = std::shared_ptr<Registration_View_Model>;

protected:
    bool m_exit = false;
    Registration m_registration;

public:
    explicit Main_View(Registration registration);
    void Enter_View();
    void Start_UI();
};


#endif //CLIENT_MAIN_VIEW_H
