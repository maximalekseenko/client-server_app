#pragma once



// buildin libraties
#include <string>
#include <fstream>



namespace login
{
    static std::string username, password;

    static std::string configFilePath;
    static std::fstream configFile;
    static bool isInited = false;
    
    /**
     * @brief login user via config file if it exists
     * 
     * @param forceNew force creation of a new config file
     */
    void Init(const char* __exePath);
    

    /**
     * @brief login user via config file if it exists
     * 
     * @param forceNew force creation of a new config file
     */
    bool Login();
    

    /**
     * @brief Reads username and password from config file
     * 
     */
    bool ReadLogin();


    /**
     * @brief Asks user to input new login information and adds em to config file
     * 
     */
    bool WriteLogin();

    std::string PassEncode();
};