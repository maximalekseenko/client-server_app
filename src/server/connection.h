#pragma once



// buildin libraries
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>



namespace connection
{
    /// @brief Socket for server.
    static int masterSocket;
    int GetMasterSocket();

    /// @brief Server address.
    static struct sockaddr_in serverAddress;

    /// @brief Server storage for ongoing connections.
    static sockaddr_storage serverStorage;

    /// @brief was this module inited before (via Init)
    static bool isInited = false;



    std::string DecodeMessage(int __message);

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