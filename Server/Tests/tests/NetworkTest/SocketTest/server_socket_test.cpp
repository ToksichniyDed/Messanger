//
// Created by Toksichniy_Ded on 13.12.2023.
//

#include "server_socket_test.h"


TEST_F(Mock_Server_Socket_Test, OpenSocketTest){

}

TEST_F(Mock_Server_Socket_Test, BindSocketTest){
    EXPECT_CALL(serverSocket, Close_Socket()).Times(0);

    serverSocket.Bind_Socket();
}

TEST_F(Mock_Server_Socket_Test, ListeningSocketTest){
    EXPECT_NO_THROW(serverSocket.Listening_Socket());

    serverSocket.Listening_Socket();
}