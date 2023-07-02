#pragma once



// buildin libraries
#include <sqlite3.h>
#include <string>
#include <vector>



namespace data
{
    struct tableDataType 
    {
        int id = -1;
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
    bool RemUser(int __id);


    std::vector<tableDataType> GetData(int __limit, int __offset);
    bool IsDataExists(int __id);
}