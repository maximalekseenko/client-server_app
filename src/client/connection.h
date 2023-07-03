#pragma once



// buildin lybraries
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



namespace connection
{
    /// @brief Was this namespace initialized before.
    static bool isInited = false;

    /// @brief Socket for client.
    static int clientSocket;

    /// @brief Server address.
    static struct sockaddr_in serverAddress;

    static pthread_t tid;


    /**
     * @brief Initializes this namespace
     * 
     */
    void Init(const char* __exePath);


    /**
     * @brief Connects this client to server
     * 
     */
    bool Connect();


    /**
     * @brief Starts client talk to server
     * 
     */
    void Start();




    /**
     * @brief Waits for server to request data
     * 
     */
    int GetRequest();


    /**
     * @brief Sents current activity
     * 
     */
    int SentActivity();


    /**
     * @brief Sent screenshot
     * 
     */
    int SentScreenshot();
};