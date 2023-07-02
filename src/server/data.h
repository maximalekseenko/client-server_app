#pragma once



// buildin libraries
#include <sqlite3.h>
#include <string>



namespace data
{
    struct tableDataType 
    {
        std::string username;
        std::string password;
        int activity;
    };

    static char* sqlMessaggeError;
    static bool isInited = false;
    static sqlite3* DB;


    void Init(const char * __exePath);

    bool CreateDB();


    bool CheckPass(const char* __username, const char* __password);


    bool Write(const char* __username, int __type);


    bool AddUser(const char* __username, const char* __password);
    bool RemUser(const char* __username, const char* __password);


    tableDataType GetData(int id);
}