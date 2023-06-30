#pragma once

#include <string>

namespace login
{
    static std::string username, password;
    static bool isLoggedIn = false;
    
    /**
     * @brief login user via config file if it exists
     * 
     * @param __path path to config file
     * @param forceNew force creation of a new config file
     */
    void Login(bool forceNew = false);

    std::string PassEncode();
};