#pragma once



// buildin libraries
#include <sqlite3.h>



namespace data
{
    static char* sqlMessaggeError;
    static bool isInited = false;
    static sqlite3* DB;


    void Init();


    void CheckPass(const char* __username, const char* __password);


    void Write(const char* __username, int __type);


    void NewUser(const char* username, const char* password);
}