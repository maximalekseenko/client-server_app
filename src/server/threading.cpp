#include "threading.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cstdio>
#include <cstdlib>

// custom libraries
#include "connection.h"
#include "data.h"



void threading::CreateThread(int __clientSocket)
{
    // create
    pthread_create(
        &threading::clientTreads[threading::clientTreadsAmount++], 
        NULL, 
        threading::ClientThread, 
        &__clientSocket
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
    char buffer[BUFFSIZE];

    // login
    recv(clientSocket, buffer, BUFFSIZE, 0);
    int _id = threading::Login(buffer);

    // loop
    if (_id > 0) 
        while (recv(clientSocket, buffer, BUFFSIZE, 0) > 0)
            send(clientSocket, "1", BUFFSIZE, 0);

    threading::Logout(_id);
    pthread_exit(NULL);
}


bool threading::IsLoggedin(int __id)
{
    return threading::loggedinUserIds.find(__id) != threading::loggedinUserIds.end();
}


int threading::Login(char __buffer[BUFFSIZE])
{
    // get password and username from buffer
    std::string _bufferSting = std::string(__buffer);
    int _separatorPosition = _bufferSting.find('\n');
    std::string _username = _bufferSting.substr(0, _separatorPosition);
    std::string _password = _bufferSting.substr(_separatorPosition+1);

    int _id = data::CheckPass(_username.c_str(), _password.c_str()).id;
    threading::loggedinUserIds.insert(_id);

    return _id;
}

void threading::Logout(int __id)
{
    threading::loggedinUserIds.extract(__id);
}