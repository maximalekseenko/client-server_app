#include "connection.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <string>


#include "login.h"


int EncodeMessage(std::string __message) {
    int _encoded = 0;

    for (int _i = 0; _i < __message.size(); _i ++) {
        _encoded = _encoded * CHARSIZE + int(__message[_i]);
    }
    return _encoded;
}

void connection::Init(const char* __exePath)
{
    if (connection::isInited) return;

    // init socket
    connection::serverAddress.sin_family = AF_INET;
    connection::serverAddress.sin_addr.s_addr = INADDR_ANY;
    connection::serverAddress.sin_port = htons(PORT);
    connection::clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    connection::isInited = true;
}



bool connection::Connect()
{
    if (connect(
        connection::clientSocket,
        (struct sockaddr*) &connection::serverAddress,
        sizeof(connection::serverAddress)
    ) < 0) {
        printf("[Error]: connection failed!\n");
        return false;
    }
    else
    {
        printf("[Info]: connection success!\n");
        return true;
    }
}


void connection::CreateThread()
{

    int _message = 10;//(login::GetUsername() + "\n" + login::GetPassword()).c_str();
    send(connection::clientSocket, "1", 1, 0);

    while (true) 
        printf("[Info]: AAA!\n");
    // int client_request = 2;
    // pthread_create(
    //     &connection::tid, 
    //     NULL, 
    //     connection::ClientThread, 
    //     NULL
    // );
    // pthread_join(connection::tid, NULL);


    // // std::string _message = login::GetUsername() + "\n" + login::GetPassword();
    // char* _message = "HI!";//(login::GetUsername() + "\n" + login::GetPassword()).c_str();
    // char buffer[BUFFSIZE] = {0};
    // // send(connection::clientSocket, _message, strlen(_message), 0);
    // send(
    //     connection::clientSocket, 
    //     &_message, 
    //     sizeof(_message), 
    //     0
    // );
    // printf("[Info]: AAA!\n");
    // read(connection::clientSocket, &_message, 1024);
    // printf("[Info]: BBB!\n");

}


void* connection::ClientThread(void* args)
{

    pthread_exit(NULL);
}