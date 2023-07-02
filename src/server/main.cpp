


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

    data::AddUser("user1", "pass1");
    data::AddUser("user2", "pass2");
    data::AddUser("user3", "pass3");
    data::AddUser("user4", "pass4");
    data::AddUser("user5", "pass5");
    data::AddUser("user6", "pass6");
    data::AddUser("user7", "pass7");
    data::AddUser("user8", "pass8");
    data::AddUser("user9", "pass9");
    data::AddUser("user10", "pass10");
    data::AddUser("user11", "pass11");
    data::AddUser("user12", "pass12");

    window::Run();
    connection::Listen();
}