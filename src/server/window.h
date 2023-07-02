#pragma once



// buildin libraries
#include <ncurses.h>
#include <string>
#include <pthread.h>
#include <functional>
#include <vector>



namespace window
{
    struct Window
    {
        WINDOW* win;

        virtual void OnOpen(){}
        virtual void OnClose(){}

        virtual void DrawBorder(){printf("F");}
        virtual void DrawText(){}
        virtual void DrawSelection(int){}

        virtual void SetCursor(){}

        virtual void ActionSelect(){}
        virtual void ActionCancel(){}
        virtual void ActionUp(){}
        virtual void ActionDown(){}
        virtual void ActionLeft(){}
        virtual void ActionRight(){}
        virtual void ActionChar(char ch){}
    };

    static std::vector<Window*> Windows;
    static int currentWindowId = 0;
    static Window* GetCurrentWindow();
    void OpenWindow(int __winID);

    static pthread_t windowThread;
    static std::string errorText;

    void Init();
    void Run();
    void* Thread(void* args);
    void GetUserInput();

    void Draw();
}