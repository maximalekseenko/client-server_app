#pragma once

#include "window.h"
#include "data.h"

#define WGLOBAL_ID 0
#define WNEWUSER_ID 1


#define WGLOBAL_H 20
#define WGLOBAL_W 50
struct WindowGlobal : window::Window
{
    WindowGlobal()
    {
        win = newwin(WGLOBAL_H, WGLOBAL_W, 0, 0);
    }
    
    void DrawBorder()
    {
        box(win, 0, 0);
    }
    void DrawText()
    {

    }
    void DrawSelection(int)
    {

    }

    void SetCursor(){}

    void ActionSelect(){ window::OpenWindow(WNEWUSER_ID); }
    void ActionCancel(){}
    void ActionUp(){}
    void ActionDown(){}

    void ActionLeft(){ ActionUp(); }
    void ActionRight(){ ActionDown(); }

    void ActionChar(char ch){ ActionDown(); }
};

#define WNEWUSER_H 4
#define WNEWUSER_W 28
struct WindowNewUser : window::Window
{
    std::string hashUsername;
    std::string hashPassword;
    bool isWrightingUsername = true;
    WindowNewUser()
    {
        win = newwin(WNEWUSER_H, WNEWUSER_W, (WGLOBAL_H - WNEWUSER_H) / 2, (WGLOBAL_W - WNEWUSER_W) / 2);
    }

    virtual void OnOpen(){
        hashUsername.clear();
        hashPassword.clear();
    }

    virtual void OnClose() { }

    void DrawBorder()
    {
        box(win, 0, 0);
        mvwaddstr(win, 0, WNEWUSER_W/2 - 9 / 2, "new user");
    }
    void DrawText()
    {
        mvwaddstr(win, 1, 1, "username:                ");
        mvwaddstr(win, 2, 1, "password:                ");


        mvwaddstr(win, 1, 10, hashUsername.c_str());
        mvwaddstr(win, 2, 10, hashPassword.c_str());
    }
    void DrawSelection(int)
    {
    }

    void SetCursor()
    {
        move(getbegy(win) + 1 + !isWrightingUsername, getbegx(win) + 10 + (isWrightingUsername ? hashUsername.size() : hashPassword.size()));
        refresh ();
    }

    void ActionSelect() 
    {
        if (hashUsername.size() == 0 || hashPassword.size() == 0) return;

        data::AddUser(hashUsername.c_str(), hashPassword.c_str());

        window::OpenWindow(WGLOBAL_ID);
    }
    void ActionCancel() { window::OpenWindow(WGLOBAL_ID); }
    void ActionUp()
    {
        isWrightingUsername = !isWrightingUsername;
    }
    void ActionDown() { ActionUp(); }
    void ActionLeft() { ActionUp(); }
    void ActionRight() { ActionUp(); }
    void ActionChar(char ch) 
    {
        std::string &editHash = isWrightingUsername ? hashUsername : hashPassword;
        
        if (ch == '\b') editHash.pop_back();
        else if (editHash.size() != 16)
            editHash = editHash + ch;
    }
};