


// settings
#define APPSERVER
#include "../settings.h"



// custom libraries
#include "connection.h"



/**
 * @brief Main function for server
 * 
 * @param argc amount of arguments passted on start
 * @param argv arguments passted on start
 * @return standart c++ exit code
 */
int main(int argc, char* argv[])
{
    connection::Init();
    data::Init();

    connection::Listen();
}