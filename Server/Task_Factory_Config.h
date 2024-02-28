//
// Created by Toksichniy_Ded on 27.02.2024.
//

#include "Modules/Business_Logic/Task/Task_Type/include/Task_Headers.h"
#include "Modules/Business_Logic/Task/include/Task_Factory.h"
#include "Modules/Business_Logic/Task/include/Task_Creator_Headers.h"

void Task_Factory_Config(){
    Task_Factory task_factory;

    task_factory.Register_Task("authorization_task", new Authorization_Task_Creator);
    task_factory.Register_Task("registration_task",new Registration_Task_Creator);
}