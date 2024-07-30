//
// Created by Toksichniy_Ded on 27.02.2024.
//

#include <memory>

#include "Modules/Business_Logic/Task/Task_Type/include/Task_Headers.h"
#include "Modules/Business_Logic/Task/include/Task_Factory.h"
#include "Modules/Business_Logic/Task/include/Authorization_Task_Creator.h"
#include "Modules/Business_Logic/Task/include/Registration_Task_Creator.h"

inline std::unique_ptr<Task_Factory> Task_Factory_Config(std::unique_ptr<Pool_Connection> poolConnection){

    auto task_factory = std::make_unique<Task_Factory>(std::move(poolConnection), std::make_unique<Task_Factory::Task_Map>()) ;

    task_factory->Register_Task("authorization_message", std::make_unique<Authorization_Task_Creator>());
    task_factory->Register_Task("registration_message",std::make_unique<Registration_Task_Creator>());

    return task_factory;
}