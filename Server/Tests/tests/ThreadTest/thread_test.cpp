//
// Created by Toksichniy_Ded on 22.12.2023.
//

#include "thread_test.h"

//TEST_F(Thread_Pool_Test, Add_Thread_Test) {
//    Thread_Creator_Mock mock_creator;
//    Thread_Mock mock_thread;
//    Task_Container task_container;
//    Container_Vector_Mock<IThread *> thread_vector;
//
//    EXPECT_CALL(mock_creator, Create_Thread(&task_container)).WillOnce(testing::Return(&mock_thread));
//    EXPECT_CALL(mock_thread, Wait_Task).Times(1);
//    EXPECT_CALL(thread_vector, Emplace_Back).Times(1);
//    Thread_Pool temp(1, &task_container, &mock_creator, &thread_vector);
//}

TEST_F(Thread_Pool_Test, Add_Thread_Test){
    Unreal_Thread_Creator creator;
    Thread_Mock mock_th;
    creator.Set_Thread(&mock_th);
    Container_Vector <IThread*> containerVector;

    EXPECT_CALL(mock_th, Wait_Task).Times(1);
    Thread_Pool pool(1, new Task_Container, &creator, &containerVector);
    containerVector.Clear();
}

TEST_F(Thread_Pool_Test, Sub_Thread_Test){
    Unreal_Thread_Creator creator;
    Thread_Mock mock_th;
    creator.Set_Thread(&mock_th);
    Container_Vector_Fake <IThread*> containerVector;
    Thread_Pool pool(2, new Task_Container, &creator, &containerVector);

    EXPECT_CALL(mock_th, Close_Thread).Times(1);
    pool.Sub_Thread(1);
    containerVector.Clear();
}