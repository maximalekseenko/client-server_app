#include "connection.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cstdio>
#include <cstdlib>
#include <pthread.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>



void connection::Init()
{
    if (connection::isInited) return;

    // init socket
    connection::clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    connection::serverAddress.sin_family = AF_INET;
    connection::serverAddress.sin_addr.s_addr = INADDR_ANY;
    connection::serverAddress.sin_port = htons(PORT);

    connection::isInited = true;
}



void connection::Connect()
{
    if (!connection::isInited) connection::Init();

    // connect
    int _connectionStatus = connect(
        connection::clientSocket,
        (struct sockaddr*)&connection::serverAddress,
        sizeof(connection::serverAddress)
    );
 
    // check for success
    if (_connectionStatus < 0) {
        printf("[Error]: connection failed!\n");
        exit(-1);
    }
    else
        printf("[Info]: connection success!\n");
}

void connection::CreateThread()
{
    int client_request = 2;
    pthread_create(
        &connection::tid, 
        NULL, 
        connection::ClientThread, 
        &client_request
    );
    pthread_join(connection::tid, NULL);
}


void* connection::ClientThread(void* args)
{
    int client_request = *((int*)args);

    send(
        connection::clientSocket, 
        &client_request, 
        sizeof(client_request), 
        0
    );
    // printf("[Info]: AAA!\n");

    pthread_exit(NULL);
}