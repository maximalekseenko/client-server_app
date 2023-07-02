#include "window.h"



// settings
#define APPSERVER
#include "../settings.h"



// buildin libraries
#include <cmath>



// custom libraries
#include "data.h"
#include "windows.h"



void window::Init()
{
    initscr();
    keypad(stdscr, TRUE);


    window::Windows = {
        new WindowGlobal(),
        new WindowNewUser()
    };

    refresh();
}


static window::Window* window::GetCurrentWindow()
{
    return window::Windows[window::currentWindowId];
}


void window::Run()
{
    pthread_create(
        &window::windowThread, 
        NULL, 
        window::Thread, 
        NULL
    );
    pthread_join(window::windowThread, NULL);
}



void* window::Thread(void* args)
{
    while (true)
    {
        window::Draw();
        window::GetCurrentWindow()->SetCursor();
        window::GetUserInput();
    }
}


void window::GetUserInput()
{
    int _inputValue = getch();
    // CANCEL
         if (_inputValue == 27) window::GetCurrentWindow()->ActionCancel();
    // UP
    else if (_inputValue == KEY_UP) window::GetCurrentWindow()->ActionUp();
    // RIGHT
    else if (_inputValue == KEY_RIGHT) window::GetCurrentWindow()->ActionRight();
    // DOWN
    else if (_inputValue == KEY_DOWN) window::GetCurrentWindow()->ActionDown();
    // LEFT
    else if (_inputValue == KEY_LEFT) window::GetCurrentWindow()->ActionLeft();
    // SELECT
    else if (_inputValue == 10) window::GetCurrentWindow()->ActionSelect();
    else if (std::isalpha(_inputValue) || std::isdigit(_inputValue)) window::GetCurrentWindow()->ActionChar(_inputValue);
    else if (_inputValue == KEY_BACKSPACE || _inputValue == KEY_DC || _inputValue == 127) window::GetCurrentWindow()->ActionChar('\b');
}


void window::Draw()
{
    werase(window::GetCurrentWindow()->win);
    window::GetCurrentWindow()->DrawBorder();
    window::GetCurrentWindow()->DrawText();
    window::GetCurrentWindow()->DrawSelection(0);

    wrefresh(window::GetCurrentWindow()->win);
}

void window::OpenWindow(int __winID)
{
    if (0 > __winID || __winID > window::Windows.size()) return; // TODO Error
    window::GetCurrentWindow()->OnClose();
    window::currentWindowId = __winID;
    window::GetCurrentWindow()->OnOpen();
}