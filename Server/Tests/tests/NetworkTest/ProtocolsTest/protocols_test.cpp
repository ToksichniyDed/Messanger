//
// Created by Toksichniy_Ded on 22.12.2023.
//

#include "protocols_test.h"

TEST_F(Protocols_Test, Authorization_Test){
    Authorization_Message test_message;
    std::string str("true");
    std::string result = test_message.Set_Parametrs().Set_Content(str).Build_Message();
    EXPECT_EQ(result, Pack_Json("authorization_data_ans","true"));
}

TEST_F(Protocols_Test, Registration_Test){
    Registration_Message test_message;
    std::string str("true");
    std::string result = test_message.Set_Parametrs().Set_Content(str).Build_Message();
    EXPECT_EQ(result, Pack_Json("registration_data_ans","true"));
}