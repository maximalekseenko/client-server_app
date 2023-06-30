#include "login.h"

#include <iostream>
#include <fstream>
#include <filesystem>


// #include "encrypt.h"



void login::Login(bool forceNew)
{
    // TODO fix file location
    std::filesystem::path configFilePath = std::filesystem::current_path() / "config";
    std::fstream configFile;

    // check if config file exists
    configFile.open(configFilePath.string(), std::fstream::in);
    if (!configFile.good())
    {
        configFile.open(configFilePath.string(), std::fstream::out);
        // create config file if does not exist
        // TODO better input
        std::cout << "Login failed. Input correct username and password:" << std::endl;
        std::cout << "username: "; std::cin >> login::username;
        std::cout << "password: "; std::cin >> login::password;

        // TODO encryption
        configFile << login::username << std::endl;
        configFile << login::password << std::endl;
    }
    else
    {
        configFile >> login::username;
        configFile >> login::password;
    }

    configFile.close();
}