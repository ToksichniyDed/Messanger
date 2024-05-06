
#include "clients_manager_test.h"

TEST_F(Clients_Manager_Test, Iteration_Test_Close_Socket){
    auto taskFactoryMock = std::make_unique<Task_Factory_Mock>();
    auto taskContainerMock = std::make_shared<Task_Container_Mock>();
    auto sk = std::make_shared<MySocketType>(123);
    auto clientSocketManagerMock = std::make_shared<Client_Socket_Manager_Mock>(sk);
    auto clientSocketMock = std::make_shared<Client_Socket_Mock>(clientSocketManagerMock,sk);
    auto vectorMock = std::make_unique<Container_Vector<std::shared_ptr<Client_Socket>>>();
    auto messageFactoryMock = std::make_unique<Message_Factory>(std::make_unique<std::unordered_map<std::string, std::unique_ptr<IMessage_Creator>>>());
    vectorMock->Emplace_Back(clientSocketMock);
    Client_Manager client_manager_test(std::move(vectorMock),taskContainerMock, std::move(taskFactoryMock), std::move(messageFactoryMock));

    EXPECT_CALL(*clientSocketMock, Get_Client_Socket_Manager).WillRepeatedly(::testing::Return(clientSocketManagerMock));
    EXPECT_CALL(*clientSocketManagerMock, Check_Socket).WillOnce(::testing::Return(false));
    EXPECT_CALL(*clientSocketMock, Get_Socket).WillOnce(::testing::Return(sk));
    EXPECT_CALL(*clientSocketManagerMock, Close_Socket).Times(1);
    client_manager_test.Iteration();
}

TEST_F(Clients_Manager_Test, Iteration_Test_Client_Message_Empty){
    auto taskFactoryMock = std::make_unique<Task_Factory_Mock>();
    auto taskFactoryPtr = taskFactoryMock.get();
    auto taskContainerMock = std::make_shared<Task_Container_Mock>();
    auto sk = std::make_shared<MySocketType>(123);
    auto clientSocketManagerMock = std::make_shared<Client_Socket_Manager_Mock>(sk);
    auto clientSocketMock = std::make_shared<Client_Socket_Mock>(clientSocketManagerMock,sk);
    auto vectorMock = std::make_unique<Container_Vector<std::shared_ptr<Client_Socket>>>();
    //auto messageFactoryMock = std::make_unique<Message_Factory>();
    std::vector<char> buf;
    std::pair<std::shared_ptr<Client_Socket>, std::vector<char>> message = std::make_pair(clientSocketMock,buf);

    vectorMock->Emplace_Back(clientSocketMock);
    Client_Manager client_manager_test(std::move(vectorMock),taskContainerMock, std::move(taskFactoryMock), std::make_unique<Message_Factory>(std::make_unique<std::unordered_map<std::string, std::unique_ptr<IMessage_Creator>>>()));

    EXPECT_CALL(*clientSocketMock, Get_Client_Socket_Manager).WillRepeatedly(::testing::Return(clientSocketManagerMock));
    EXPECT_CALL(*clientSocketManagerMock, Check_Socket).WillOnce(::testing::Return(true));
    EXPECT_CALL(*clientSocketMock, Listen_Socket).WillOnce(::testing::Return(message));
    EXPECT_CALL(*taskFactoryPtr, Create_Task).Times(0);

    client_manager_test.Iteration();
}

TEST_F(Clients_Manager_Test, Iteration_Test_Client_Message_Not_Empty_Fail_Message_Type){
    auto taskFactoryMock = std::make_unique<Task_Factory_Mock>();
    auto taskFactoryPtr = taskFactoryMock.get();
    auto taskContainerMock = std::make_shared<Task_Container_Mock>();
    auto sk = std::make_shared<MySocketType>(123);
    auto clientSocketManagerMock = std::make_shared<Client_Socket_Manager_Mock>(sk);
    auto clientSocketMock = std::make_shared<Client_Socket_Mock>(clientSocketManagerMock,sk);
    auto vectorMock = std::make_unique<Container_Vector<std::shared_ptr<Client_Socket>>>();
    auto messageFactoryMock = std::make_unique<Message_Factory_Mock>();
    auto messageFactoryPtr = messageFactoryMock.get();
    std::vector<char> buf;
    std::string msg = Pack_Json("type","data");
    buf.insert(buf.end(),msg.begin(),msg.end());
    std::pair<std::shared_ptr<Client_Socket>, std::vector<char>> message = std::make_pair(clientSocketMock,buf);

    vectorMock->Emplace_Back(clientSocketMock);
    Client_Manager client_manager_test(std::move(vectorMock),taskContainerMock, std::move(taskFactoryMock), std::move(messageFactoryMock));

    EXPECT_CALL(*clientSocketMock, Get_Client_Socket_Manager).WillRepeatedly(::testing::Return(clientSocketManagerMock));
    EXPECT_CALL(*clientSocketManagerMock, Check_Socket).WillOnce(::testing::Return(true));
    EXPECT_CALL(*clientSocketMock, Listen_Socket).WillOnce(::testing::Return(message));
    EXPECT_CALL(*messageFactoryPtr, Create_Message).WillOnce(::testing::Return(nullptr));
    EXPECT_CALL(*taskFactoryPtr, Create_Task).Times(0);
    EXPECT_CALL(*clientSocketMock, Send_Message).Times(1);

    client_manager_test.Iteration();
}

TEST_F(Clients_Manager_Test, Iteration_Test_Client_Message_Not_Empty_Real_Task_Type){
    auto taskFactoryMock = std::make_unique<Task_Factory_Mock>();
    auto taskFactoryPtr = taskFactoryMock.get();
    auto taskContainerMock = std::make_shared<Task_Container_Mock>();
    auto sk = std::make_shared<MySocketType>(123);
    auto clientSocketManagerMock = std::make_shared<Client_Socket_Manager_Mock>(sk);
    auto clientSocketMock = std::make_shared<Client_Socket_Mock>(clientSocketManagerMock,sk);
    auto vectorMock = std::make_unique<Container_Vector<std::shared_ptr<Client_Socket>>>();
    auto messageFactoryMock = std::make_unique<Message_Factory_Mock>();
    auto messageFactoryPtr = messageFactoryMock.get();
    std::vector<char> buf;
    std::string msg = Pack_Json("type","data");
    buf.insert(buf.end(),msg.begin(),msg.end());
    std::pair<std::shared_ptr<Client_Socket>, std::vector<char>> message = std::make_pair(clientSocketMock,buf);

    vectorMock->Emplace_Back(clientSocketMock);
    Client_Manager client_manager_test(std::move(vectorMock),taskContainerMock, std::move(taskFactoryMock), std::move(messageFactoryMock));

    EXPECT_CALL(*clientSocketMock, Get_Client_Socket_Manager).WillRepeatedly(::testing::Return(clientSocketManagerMock));
    EXPECT_CALL(*clientSocketManagerMock, Check_Socket).WillOnce(::testing::Return(true));
    EXPECT_CALL(*clientSocketMock, Listen_Socket).WillOnce(::testing::Return(message));
    EXPECT_CALL(*messageFactoryPtr, Create_Message).WillOnce(::testing::Return(std::make_unique<Authorization_Message>(msg)));
    EXPECT_CALL(*taskFactoryPtr, Create_Task).WillOnce
    (::testing::Return(std::make_unique<Authorization_Task>(nullptr, nullptr, nullptr, nullptr)));
    EXPECT_CALL(*taskContainerMock, Emplace_Task).Times(1);
    EXPECT_CALL(*taskContainerMock, Notify_All).Times(1);

    client_manager_test.Iteration();

}