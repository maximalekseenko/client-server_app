#pragma once


// settings
#define APPSERVER
#include "../settings.h"


#include <pthread.h>
#include <vector>
#include <set>



namespace threading
{
    /// @brief Array of ongoing client threads.
    static pthread_t clientTreads[CLIENTSLIMIT];

    /// @brief Amount of elements in clientTreads.
    static int clientTreadsAmount = 0;
    

    /**
     * @brief Create a Thread object
     * 
     * @param __clientSocket socket of a client for new socket
     */
    void CreateThread(int __clientSocket);


    /**
     * @brief Thread for a client
     * 
     * @param param 
     * @return void* 
     */
    void* ClientThread (void* param);

    
    /**
     * @brief Updates current threads.
     * 
     */
    void Update();


    static std::set<int> loggedinUserIds;
    bool IsLoggedin(int __id);

    /**
     * @brief Logins user by checking password then adding id to loggedinUserIds;
     * 
     * @return int 
     */
    int Login(char __buffer[BUFFSIZE]);

    /// @brief Logout
    void Logout(int __id);
};