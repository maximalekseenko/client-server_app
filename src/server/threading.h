#pragma once


// settings
#define APPSERVER
#include "../settings.h"


#include <pthread.h>



namespace threading
{
    /// @brief Array of ongoing client threads.
    static pthread_t clientTreads[CLIENTSLIMIT];

    /// @brief Amount of elements in clientTreads.
    static int clientTreadsAmount = 0;
    

    /**
     * @brief Create a Thread object
     * 
     * @param clientSocket socket of a client for new socket
     */
    void CreateThread(int clientSocket);


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
};