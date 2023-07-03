


// settings
#define APPCLIENT
#include "../settings.h"



// custom libraries
#include "connection.h"
#include "login.h"



/**
 * @brief Main function for client
 * 
 * @param argc amount of arguments passted on start
 * @param argv arguments passted on start
 * @return standart c++ exit code
 */
int main (int argc, char* argv[])
{
    login::Init(argv[0]);
    connection::Init(argv[0]);

    login::Login();

    connection::Connect();

    connection::Start();
}