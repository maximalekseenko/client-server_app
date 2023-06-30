


// settings
#define APPCLIENT
#include "../settings.h"



// custom libraries
#include "connection.h"



/**
 * @brief Main function for client
 * 
 * @param argc amount of arguments passted on start
 * @param argv arguments passted on start
 * @return standart c++ exit code
 */
int main (int argc, char* argv[])
{
    connection::Connect();

    connection::CreateThread();

    // connection::SentData(321);
}