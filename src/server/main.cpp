


// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cstdio>
#include <cstdlib>


// custom libraries
#include "connection.h"
#include "data.h"
#include "threading.h"



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
    // threading::Init();

    data::NewUser("AAA", "BBB");

    connection::Listen();
}