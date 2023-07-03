#include "threading.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cstdio>
#include <cstdlib>



// custom libraries
#include "connection.h"

#include <errno.h>



void threading::CreateThread(int clientSocket)
{
    // create
    pthread_create(
        &threading::clientTreads[threading::clientTreadsAmount++], 
        NULL, 
        threading::ClientThread, 
        &clientSocket
    );

    // update
    threading::Update();
}


void threading::Update()
{
    // there is still some space for a new client
    if (clientTreadsAmount < CLIENTSLIMIT) return;

    // cleanup
    clientTreadsAmount = 0;
    for (int i = 0; i < 50; i++) pthread_join(threading::clientTreads[i++], NULL);

}


void* threading::ClientThread (void* param)
{
    int clientSocket = *(int*)param;
    // printf("Connection!\n");


        // std::string _message;
        // recv(connection::GetMasterSocket(), &_message, BUFFSIZE, 0);
        // printf("%s\n",_message.c_str());

    char buffer[255];
    // while (true)
    // {
    //     // poll();
    //     // auto log = read(clientSocket, &buffer, BUFFSIZE);
    // }
    recv(clientSocket, buffer, sizeof(buffer), 0);
    // printf("FUCK THE %s\n", strerror(errno));
    // printf("%s\n", buffer);

    pthread_exit(NULL);
}