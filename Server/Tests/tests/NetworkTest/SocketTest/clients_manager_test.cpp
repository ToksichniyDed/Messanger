
#include "clients_manager_test.h"

TEST_F(Clients_Manager_Test, Iteration_Test_Close_Socket){
    Task_Factory_Mock taskFactoryMock;
    Task_Container_Mock taskContainerMock;
    SOCKET sk = 123;
    Client_Socket_Mock clientSocketMock(sk);
    Container_Vector<Client_Socket*> vectorMock;
    Client_Socket_Manager_Mock clientSocketManagerMock(&sk);

    Client_Manager client_manager_test(&vectorMock, &taskContainerMock,  &taskFactoryMock);
    vectorMock.Emplace_Back(&clientSocketMock);

    EXPECT_CALL(clientSocketMock, Get_Client_Socket_Manager).WillRepeatedly(::testing::Return(&clientSocketManagerMock));
    EXPECT_CALL(clientSocketManagerMock, Check_Socket).WillOnce(::testing::Return(false));
    EXPECT_CALL(clientSocketMock, Get_Socket).Times(1);
    EXPECT_CALL(clientSocketManagerMock, Close_Socket).Times(1);
    EXPECT_CALL(clientSocketMock, Delete_Object).Times(1);
    client_manager_test.Iteration();
}

TEST_F(Clients_Manager_Test, Iteration_Test_Client_Message_Empty){
    Task_Factory_Mock taskFactoryMock;
    Task_Container_Mock taskContainerMock;
    SOCKET sk = 123;
    Client_Socket_Mock clientSocketMock(sk);
    Container_Vector<Client_Socket*> vectorMock;
    Client_Socket_Manager_Mock clientSocketManagerMock(&sk);
    std::vector<char> buf;
    std::pair<Client_Socket *, std::vector<char>> message = std::make_pair(&clientSocketMock,buf);

    Client_Manager client_manager_test(&vectorMock, &taskContainerMock,  &taskFactoryMock);
    vectorMock.Emplace_Back(&clientSocketMock);

    EXPECT_CALL(clientSocketMock, Get_Client_Socket_Manager).WillRepeatedly(::testing::Return(&clientSocketManagerMock));
    EXPECT_CALL(clientSocketManagerMock, Check_Socket).WillOnce(::testing::Return(true));
    EXPECT_CALL(clientSocketMock, Listen_Socket).WillOnce(::testing::Return(message));
    EXPECT_CALL(taskFactoryMock, CreateTask).Times(0);

    client_manager_test.Iteration();
}

TEST_F(Clients_Manager_Test, Iteration_Test_Client_Message_Not_Empty){
    Task_Factory_Mock taskFactoryMock;
    Task_Container_Mock taskContainerMock;
    SOCKET sk = 123;
    Client_Socket_Mock clientSocketMock(sk);
    Container_Vector<Client_Socket*> vectorMock;
    Client_Socket_Manager_Mock clientSocketManagerMock(&sk);
    std::vector<char> buf;
    std::string msg = Pack_Json("type","data");
    buf.insert(buf.end(),msg.begin(),msg.end());
    std::pair<Client_Socket *, std::vector<char>> message = std::make_pair(&clientSocketMock,buf);

    Client_Manager client_manager_test(&vectorMock, &taskContainerMock,  &taskFactoryMock);
    vectorMock.Emplace_Back(&clientSocketMock);

    EXPECT_CALL(clientSocketMock, Get_Client_Socket_Manager).WillRepeatedly(::testing::Return(&clientSocketManagerMock));
    EXPECT_CALL(clientSocketManagerMock, Check_Socket).WillOnce(::testing::Return(true));
    EXPECT_CALL(clientSocketMock, Listen_Socket).WillOnce(::testing::Return(message));
    EXPECT_CALL(taskFactoryMock, CreateTask).Times(1);
    EXPECT_CALL(taskContainerMock, Notify_All).Times(1);

    client_manager_test.Iteration();
}