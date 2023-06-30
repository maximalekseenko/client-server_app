#include "data.h"



#include <string>
#include <cstdio>
#include <cstdlib>



void data::Init()
{
    if (data::isInited) return;

    sqlite3_open("server.sqlite", &data::DB);

    // if table does not exists, create new
    if (! sqlite3_exec(
        data::DB, 
        "select count(type) from sqlite_master where type='table' and name='EMPLOYEE'",
        NULL,
        0,
        &data::sqlMessaggeError
    ))
        sqlite3_exec(
            data::DB, 
            "CREATE TABLE EMPLOYEE(\
            USERNAME    TEXT    PRIMARY KEY     NOT NULL,\
            PASSWORD    TEXT                    NOT NULL,\
            ACTIVITY    INT                     NOT NULL);", 
            NULL,
            0, 
            NULL
        );

    data::isInited = true;
}

void data::NewUser(const char* username, const char* password)
{
    if (sqlite3_exec(
        data::DB, 
        ((std::string)"INSERT INTO EMPLOYEE VALUES('" + username + "', '" + password + "', 0);").c_str(), 
        NULL, 
        0, 
        &data::sqlMessaggeError
    ))
        printf("[SQLError]: %s\n", data::sqlMessaggeError);

}