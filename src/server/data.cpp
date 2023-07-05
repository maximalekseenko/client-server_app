#include "data.h"



// #include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <filesystem> 



void data::Init(const char * __exePath)
{
    if (data::isInited) return;

    sqlite3_open((std::filesystem::path(__exePath).parent_path() / "server.sqlite").c_str(), &data::DB);

    // if db does not exists, create new
    if (sqlite3_exec(
        data::DB, 
        "SELECT COUNT(type) FROM sqlite_master WHERE type='table' AND name='EMPLOYEE'",
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
        ID          INTEGER PRIMARY KEY,          \
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

bool data::RemUser(int __id)
{
    if (sqlite3_exec(
        data::DB, 
        ((std::string)"DELETE FROM EMPLOYEE WHERE ID = " + std::to_string(__id) + ";").c_str(), 
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



static int callbackGetUserList(void* __arg, int __argc, char** __argv, char** __argn)
{
    auto _harvestedData = (std::vector<data::tableDataType> *)__arg;
    _harvestedData->push_back(data::tableDataType({std::stoi(__argv[0]), __argv[1], __argv[2], std::stoi(__argv[3])}));
    return 0;
}

std::vector<data::tableDataType> data::GetData(int __limit, int __offset)
{
    if (__offset < 0 || __limit <= 0) return std::vector<data::tableDataType>();

    std::vector<data::tableDataType> _result;
    int ret = sqlite3_exec(
        data::DB, 
        ((std::string)"SELECT * FROM EMPLOYEE " + " LIMIT " + std::to_string(__limit) + " OFFSET " + std::to_string(__offset) + ";").c_str(), 
        callbackGetUserList,
        &_result,
        &data::sqlMessaggeError
    );

    if (ret != SQLITE_OK) {
        // printf("[SQLError]: %s\n", data::sqlMessaggeError);
    }
    return _result;

    // return;
}

bool data::IsDataExists(int __id)
{
    return sqlite3_exec(
        data::DB, 
        ((std::string)"SELECT COUNT(1) FROM EMPLOYEE WHERE ID = " + std::to_string(__id) + ";").c_str(), 
        NULL,
        0,
        &data::sqlMessaggeError
    );
}



static int callbackCheckPass(void* __arg, int __argc, char** __argv, char** __argn)
{
    auto _harvestedData = (data::tableDataType *)__arg;
    *_harvestedData = data::tableDataType({std::stoi(__argv[0]), __argv[1], __argv[2], std::stoi(__argv[3])});
    return 0;
}

data::tableDataType data::CheckPass(const char* __username, const char* __password)
{
    data::tableDataType _return;
    sqlite3_exec(
        data::DB, 
        ((std::string)"SELECT * FROM EMPLOYEE WHERE USERNAME = '" + __username + "' AND PASSWORD = '" + __password + "';").c_str(), 
        callbackCheckPass,
        &_return,
        &data::sqlMessaggeError
    );
    return _return;
}
