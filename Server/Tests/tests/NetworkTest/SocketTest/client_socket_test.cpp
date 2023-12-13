//
// Created by Toksichniy_Ded on 12.12.2023.
//

#include "client_socket_test.h"

TEST_F(Mock_Client_Socket_Test, ListenSocketSuccess) {
    std::vector<char> expectedData = {'T', 'e', 's', 't'};
    EXPECT_CALL(mock_socket, Listen_Socket()).WillOnce(::testing::Return(std::make_pair(nullptr, expectedData)));

    auto result = mock_socket.Listen_Socket();

    EXPECT_EQ(result.second, expectedData);
}

TEST_F(Mock_Client_Socket_Test, ListenSocketException) {
    EXPECT_CALL(mock_socket, Listen_Socket()).WillOnce(::testing::Throw(std::runtime_error("No message to read!")));
    EXPECT_THROW(mock_socket.Listen_Socket(), std::runtime_error);
}

TEST_F(Mock_Client_Socket_Test, SendMessageSuccess) {
    std::string message = "hello";
    EXPECT_CALL(mock_socket, Send_Message(message)).Times(1);
    ASSERT_NO_THROW(mock_socket.Send_Message(message));
}

TEST_F(Mock_Client_Socket_Test, SendMessageException){
    std::string message = "hello";
    EXPECT_CALL(mock_socket, Send_Message(message)).WillOnce(::testing::Throw(std::runtime_error("Failed send message!")));
    EXPECT_THROW(mock_socket.Send_Message(message), std::runtime_error);
}

TEST_F(Mock_Client_Socket_Test, GetClientSocketTest) {
    auto result = mock_socket.Get_Socket();
    SOCKET expected_result = 0;
    EXPECT_EQ(result, expected_result);
}

TEST_F(Mock_Client_Socket_Test, GetClientSocketManagerTest) {
    SOCKET socket = 123;
    Mock_Client_Socket_Manager mockManager(socket);
    EXPECT_CALL(mock_socket, Get_Client_Socket_Manager()).WillOnce(::testing::Return(&mockManager));
    Client_Socket_Manager* manager = mock_socket.Get_Client_Socket_Manager();
    ASSERT_EQ(manager, &mockManager);
}

TEST_F(Mock_Client_Socket_Manager_Test, ClientSocketCloseTest) {
    SOCKET socket = 123;
    Mock_Client_Socket_Manager socketManager(socket);
    EXPECT_CALL(socketManager, Close_Socket()).WillOnce(::testing::Invoke([&socket]()
    {socket = INVALID_SOCKET;}));
    socketManager.Close_Socket();
    EXPECT_EQ(socket,INVALID_SOCKET);
}

TEST_F(Mock_Client_Socket_Manager_Test, CheckSocketTestFalse) {
    Mock_Client_Socket_Manager socketManager(INVALID_SOCKET);
    EXPECT_CALL(socketManager, Check_Socket()).Times(1);
    EXPECT_EQ(socketManager.Check_Socket(), false);
}