#include "connection.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <string>
#include <arpa/inet.h>


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
    connection::clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    connection::serverAddress.sin_family = AF_INET;
    connection::serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, ADDRESS, &connection::serverAddress.sin_addr) < 0)
        printf("[Error]: server unavaliable!\n");
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


void connection::Start()
{
    // login
    std::string _message = (login::GetUsername() + "\n" + login::GetPassword()).c_str();
    send(connection::clientSocket, _message.c_str(), BUFFSIZE, 0);

    char _buffer[BUFFSIZE];
    while (recv(connection::clientSocket, _buffer, BUFFSIZE, 0) > 0)
        send(connection::clientSocket, "1", BUFFSIZE, 0);
}
