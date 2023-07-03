#include "window.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cmath>
#include <locale>
#include <codecvt>

// custom libraries
#include "data.h"
#include "windows.h"



void window::Init()
{
    // init ncurses
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);

    // init windows
    window::Windows = {
        new WindowGlobal(),
        new WindowNewUser()
    };
    refresh();
} // window::Init


static window::Window* window::GetCurrentWindow() 
{ 
    return window::Windows[window::currentWindowId]; 
} // window::GetCurrentWindow


void window::Run()
{
    // start main thread
    pthread_create(&window::mainThread, NULL, window::MainThread, NULL);
    // pthread_join(window::mainThread, NULL); // TODO: FINISH
    // pthread_exit(NULL);
} // window::Run


void* window::MainThread(void* args)
{
    // main loop
    while (true)
    {
        window::Draw();
        window::GetCurrentWindow()->SetCursor();
        window::GetUserInput();
    }
} // window::MainThread


void window::GetUserInput()
{
    int _inputValue = getch();
    // CANCEL
    if (_inputValue == 27) 
        window::GetCurrentWindow()->ActionCancel();
    // UP
    else if (_inputValue == KEY_UP) 
        window::GetCurrentWindow()->ActionUp();
    // RIGHT
    else if (_inputValue == KEY_RIGHT) 
        window::GetCurrentWindow()->ActionRight();
    // DOWN
    else if (_inputValue == KEY_DOWN) 
        window::GetCurrentWindow()->ActionDown();
    // LEFT
    else if (_inputValue == KEY_LEFT) 
        window::GetCurrentWindow()->ActionLeft();
    // SELECT
    else if (_inputValue == 10) 
        window::GetCurrentWindow()->ActionSelect();
    // CHAR
    else if (std::isalpha(_inputValue) || std::isdigit(_inputValue)) 
        window::GetCurrentWindow()->ActionChar(_inputValue);
    // CHAR
    else if (_inputValue == KEY_BACKSPACE || _inputValue == KEY_DC || _inputValue == 127) 
        window::GetCurrentWindow()->ActionChar('\b');
} // window::GetUserInput


void window::Draw()
{
    // clear current window
    werase(window::GetCurrentWindow()->win);

    // draw current window
    window::GetCurrentWindow()->Draw();

    // refresh current window
    wrefresh(window::GetCurrentWindow()->win);
} // window::Draw


void window::OpenWindow(int __winID)
{
    // validate __winID for being in range of window::Windows
    if (0 > __winID || __winID > window::Windows.size()) return;

    // close previous current window
    window::GetCurrentWindow()->OnClose();

    // set current window
    window::currentWindowId = __winID;

    // open new current window
    window::GetCurrentWindow()->OnOpen();
} // window::OpenWindow