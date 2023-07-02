#include "data.h"



#include <string>
#include <cstdio>
#include <cstdlib>



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
        "CREATE TABLE EMPLOYEE(               \
        USERNAME    TEXT    UNIQUE  NOT NULL, \
        PASSWORD    TEXT            NOT NULL, \
        ACTIVITY    INT             NOT NULL);", 
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
        ((std::string)"INSERT INTO EMPLOYEE VALUES('" + username + "', '" + password + "', 0);").c_str(), 
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



static int callbackGetUserList(void* result, int argc, char** argv, char** azColName)
{
    int i;
    // fprintf(stderr, "%s: ", (const char*)result);
  
    for (i = 0; i < argc; i++) {
        // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    // printf("AAA\n");
    return 0;
}

data::tableDataType data::GetData(int id)
{
    data::tableDataType result;
    int ret = sqlite3_exec(
        data::DB, 
        "SELECT * FROM EMPLOYEE", 
        callbackGetUserList, 
        &result, 
        &data::sqlMessaggeError
    );

    if (ret != SQLITE_OK) {
        // printf("[SQLError]: %s\n", data::sqlMessaggeError);
    }
    // printf("[AAA]: %lu\n", result);

    // return;
}