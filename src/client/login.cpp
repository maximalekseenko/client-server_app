#include "login.h"



// buildin libraries
#include <iostream>
#include <filesystem>

std::string login::GetUsername() { return login::username; }
std::string login::GetPassword() { return login::password; }


void login::Init(const char* __exePath)
{
    login::configFilePath = ((std::string)__exePath).substr(0, ((std::string)__exePath).find_last_of("\\/")) + "/config";

    login::isInited = true;
}


bool login::Login()
{
    if (!login::ReadLogin())
        return login::WriteLogin();
        
    return true;
}


bool login::ReadLogin()
{
    // check if exists
    login::configFile.open(login::configFilePath, std::fstream::in);
    if (!configFile.good()) 
    {
        login::configFile.close();
        return false;
    }

    // clear
    login::username.clear();
    login::password.clear();

    // read
    login::configFile >> login::username;
    login::configFile >> login::password;
    login::configFile.close();

    // check if readed correctly
    if (login::username.empty() || login::password.empty())
    {
        return false;
    }

    return true;
}


bool login::WriteLogin()
{
    if (!login::isInited) return false; // TODO ERROR

    // get new login data
    std::cout << "please input your username and password." << std::endl;
    std::cout << "username: "; std::cin >> login::username;
    std::cout << "password: "; std::cin >> login::password;

    // write
    login::configFile.open(login::configFilePath, std::fstream::out | std::fstream::trunc);
    login::configFile << login::username << std::endl;
    login::configFile << login::password << std::endl;
    login::configFile.close();

    return true;
}