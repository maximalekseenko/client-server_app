


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
#include "window.h"


#include <locale>
#include <codecvt>



/**
 * @brief Main function for server
 * 
 * @param argc amount of arguments passted on start
 * @param argv arguments passted on start
 * @return standart c++ exit code
 */
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    connection::Init();
    data::Init(argv[0]);
    window::Init();

    window::Run();
    connection::Listen();
}