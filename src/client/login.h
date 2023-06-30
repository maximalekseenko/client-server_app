#pragma once



// buildin libraties
#include <string>



namespace login
{
    static std::string username, password;
    static bool isLoggedIn = false;
    
    /**
     * @brief login user via config file if it exists
     * 
     * @param forceNew force creation of a new config file
     */
    void Login(bool forceNew = false);

    std::string PassEncode();
};