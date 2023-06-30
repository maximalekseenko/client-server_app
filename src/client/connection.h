#pragma once



// buildin lybraries
#include <netinet/in.h>



namespace connection
{
    /// @brief Was this namespace initialized before.
    static bool isInited = false;

    /// @brief Socket for client.
    static int clientSocket;

    /// @brief Server address.
    static struct sockaddr_in serverAddress;

    static pthread_t tid;
    void CreateThread();


    /**
     * @brief Initializes this namespace
     * 
     */
    void Init();


    /**
     * @brief Connects this client to server
     * 
     */
    void Connect();


    /**
     * @brief Thread for client
     * 
     */
    void* ClientThread(void* args);
};