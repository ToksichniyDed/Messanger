//
// Created by Toksichniy_Ded on 22.12.2023.
//

#ifndef SERVER_THREAD_TEST_H
#define SERVER_THREAD_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../../Thread/Thread.h"
#include "../../../Thread/Pool/Thread_Pool.h"
#include "../../../Thread/Pool/Task_Container.h"

class Thread_Mock : public IThread {
public:
    ~Thread_Mock() override = default;

    MOCK_METHOD (void, Close_Thread, (), (override));
    MOCK_METHOD(void, Take_Task, (Task * ), (override));
    MOCK_METHOD(void, Wait_Task, (), (override));
};

class Thread_Creator_Mock : public Thread_Creator {
public:
    Thread_Creator_Mock() = default;

    MOCK_METHOD(IThread*, Create_Thread, (Task_Container * ), (override));
};

class Unreal_Thread_Creator : public Thread_Creator {
protected:
    IThread *thread;

public:
    IThread *Create_Thread(Task_Container *temp) override {
        return thread;
    }

    void Set_Thread(IThread *temp) {
        thread = temp;
    }
};

template<typename T>
class Container_Vector_Fake : public Container_Vector<T> {
protected:
    int num;
    T obj;

public:
    int Size() override { return num; }

    void Set_Size(int a) { num = a; }

    T &At(int temp) override { return obj;}
};

class Thread_Pool_Test : public testing::Test {
};

#endif //SERVER_THREAD_TEST_H
