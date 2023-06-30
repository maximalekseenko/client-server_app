#include "threading.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cstdio>
#include <cstdlib>



void threading::CreateThread(int* clientSocket)
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
    printf("Connection!\n");
    
    pthread_exit(NULL);
}