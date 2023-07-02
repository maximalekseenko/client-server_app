#include "data.h"



// #include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>



void data::Init(const char * __exePath)
{
    if (data::isInited) return;

    sqlite3_open((((std::string)__exePath).substr(0, ((std::string)__exePath).find_last_of("\\/")) + "/server.sqlite").c_str(), &data::DB);

    // if db does not exists, create new
    if (sqlite3_exec(
        data::DB, 
        "select count(type) from sqlite_master where type='table' and name='EMPLOYEE'",
        NULL,
        0,
        &data::sqlMessaggeError
    ) == SQLITE_OK) 
        data::CreateDB();

    data::isInited = true;
}



bool data::CreateDB()
{
    if (sqlite3_exec(
        data::DB, 
        "CREATE TABLE EMPLOYEE(                   \
        ID          INTEGER PRIMARY KEY, \
        USERNAME    TEXT    UNIQUE      NOT NULL, \
        PASSWORD    TEXT                NOT NULL, \
        ACTIVITY    INT                 NOT NULL);", 
        NULL,
        0, 
        &data::sqlMessaggeError
    ) != SQLITE_OK)
    {
        // printf("[SQLError]: %s\n", data::sqlMessaggeError);
        return false;
    }
    return true;
}



bool data::AddUser(const char* username, const char* password)
{
    if (sqlite3_exec(
        data::DB, 
        ((std::string)"INSERT INTO EMPLOYEE (USERNAME, PASSWORD, ACTIVITY) VALUES('" + username + "', '" + password + "', 0);").c_str(), 
        NULL, 
        0, 
        &data::sqlMessaggeError
    ) != SQLITE_OK)
    {
        // printf("[SQLError]: %s\n", data::sqlMessaggeError);
        return false;
    }
    return true;
}



static int callbackGetUserList(void* __userData, int __argc, char** __argv, char** __argn)
{
    auto _result = (data::tableDataType *)__userData;
    // _result->id = __argv[0];
    _result->username = __argv[1];
    _result->password = __argv[2];
    _result->activity = std::stoi(__argv[3]);
    return 0;
}

data::tableDataType data::GetData(int __id)
{
    data::tableDataType result;
    int ret = sqlite3_exec(
        data::DB, 
        ((std::string)"SELECT * FROM EMPLOYEE WHERE ID = " + std::to_string(__id) + " LIMIT 1").c_str(), 
        callbackGetUserList,
        &result,
        &data::sqlMessaggeError
    );

    if (ret != SQLITE_OK) {
        // printf("[SQLError]: %s\n", data::sqlMessaggeError);
    }
    return result;

    // return;
}