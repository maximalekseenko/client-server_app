#include "connection.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cstdio>
#include <cstdlib>



// custom libraries
#include "threading.h"


int connection::GetMasterSocket() { return connection::masterSocket; }


std::string DecodeMessage(int __message)
{

}



void connection::Start()
{
    connection::Init();
    connection::Listen();
}


void connection::Init()
{
    if (connection::isInited) return;

    // setup master socket
    connection::masterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connection::serverAddress.sin_family = AF_INET;
    connection::serverAddress.sin_addr.s_addr = INADDR_ANY;
    connection::serverAddress.sin_port = htons(PORT);
    
    // bind socket
    bind(connection::masterSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    // start listening
    if (listen(connection::masterSocket, CLIENTSLIMIT) == 0)
        printf("[Info]: Listening\n");
    else
        printf("[Error]: Server init failed.\n");
    
    connection::isInited = true;
}


void connection::Listen()
{
    if (!connection::isInited) connection::Init();

    /// @brief Size of ongoing connections.
    socklen_t addressSize;

    /// @brief Socket of a new client.
    int newClientSocket;

    // wait for connections
    while (true)
    {
        addressSize = sizeof(serverStorage);
        // printf("[Info]: Server is listening...\n");

        // wait for new client
        newClientSocket = accept(masterSocket, (struct sockaddr *)&serverStorage, &addressSize);

        // create thread for new client
        threading::CreateThread(newClientSocket);
    }
}
