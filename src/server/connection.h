#pragma once



// buildin libraries
#include <netinet/in.h>



namespace connection
{
    /// @brief Socket for server.
    static int masterSocket;

    /// @brief Server address.
    static struct sockaddr_in serverAddress;

    /// @brief Server storage for ongoing connections.
    static sockaddr_storage serverStorage;

    /// @brief was this module inited before (via Init)
    static bool isInited = false;


    /**
     * @brief 
     * 
     */
    void Start();


    /**
     * @brief Initializes server by creating and binding masterSocket and opening it for listening.
     * 
     */
    void Init();


    /**
     * @brief Listens for incoming connections and creates threads for them.
     * 
     */
    void Listen();
};