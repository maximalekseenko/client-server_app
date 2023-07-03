#pragma once



// custom libraries
#include "window.h"
#include "data.h"
#include "threading.h"



// ids in window::Windows
#define WGLOBAL_ID 0
#define WNEWUSER_ID 1



#define WGLOBAL_H 20
#define WGLOBAL_W 50
#define WGLOBAL_USERSTOSHOW 10
struct WindowGlobal : window::Window
{
    /// @brief cursor position
    int selectedUserDataNum = 0;
    /// @brief user list offset
    int showedUserDataOffset = 0;
    /// @brief hashed selected user
    data::tableDataType selectedUser;
    WindowGlobal()
    { 
        win = newwin(
            WGLOBAL_H, 
            WGLOBAL_W, 
            0, 
            0
        ); 
    }

    void Draw()
    {
        DrawBorder();
        DrawUsers();
        DrawText();
    }
    
    void DrawBorder()
    {
        box(win, 0, 0);
    }
    void DrawUsers()
    {
        // clear hashed selected user
        selectedUser = data::tableDataType();

        // get list of users
        auto _userDataToShow = data::GetData(WGLOBAL_USERSTOSHOW, showedUserDataOffset);

        // draw top "there is more"
        if (data::GetData(1, showedUserDataOffset - 1).size()) mvwaddstr(win, 1, 1, "  ...");

        // draw user list
        for (int i = 0; i < _userDataToShow.size(); i ++)
        {
            auto _userData = &_userDataToShow[i];

            // hash selected user
            if (i == selectedUserDataNum) selectedUser = *_userData;

            mvwaddstr(win, 2 + i, 1, (
                std::to_string(_userData->id)
            ).c_str());
            mvwaddstr(win, 2 + i, 4, (
                 _userData->username
            ).c_str());
            mvwaddstr(win, 2 + i, 20,
                threading::IsLoggedin(_userData->id) ? "◉" : "◯"
            );
        }

        // draw bottom "there is more"
        if (data::GetData(1, showedUserDataOffset + WGLOBAL_USERSTOSHOW).size()) mvwaddstr(win, WGLOBAL_USERSTOSHOW + 2, 1, "  ...");
    }
    void DrawText()
    {

        // hints
        mvwaddstr(win, WGLOBAL_H - 2, 1, "[n]: new user; [e]: delete user");
    }

    void SetCursor()
    {
        move( // location of selected user
            getbegy(win) + 2 + selectedUserDataNum, 
            getbegx(win) + 1
        );
        refresh ();
    }

    void ActionSelect(){ window::OpenWindow(WNEWUSER_ID); }

    void ActionUp()
    {
        // move cursor up
        if (selectedUserDataNum == 0)
        {
            if (data::GetData(1, showedUserDataOffset - 1).size())
                showedUserDataOffset --;
        }
        else selectedUserDataNum --;
    }
    void ActionDown()
    {
        // move cursor down
        if (selectedUserDataNum == WGLOBAL_USERSTOSHOW -1)
        {
            if (data::GetData(1, showedUserDataOffset + WGLOBAL_USERSTOSHOW).size())
                showedUserDataOffset ++;
        }
        else selectedUserDataNum ++;
    }
    void ActionLeft(){ ActionUp(); }
    void ActionRight(){ ActionDown(); }

    void ActionChar(char ch)
    {
        if (ch == 'n') window::OpenWindow(WNEWUSER_ID);
        if (ch == 'e') data::RemUser(selectedUser.id);
    }
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
        win = newwin(
            WNEWUSER_H, 
            WNEWUSER_W, 
            (WGLOBAL_H - WNEWUSER_H) / 2, 
            (WGLOBAL_W - WNEWUSER_W) / 2
        );
    }

    virtual void OnOpen(){
        hashUsername.clear();
        hashPassword.clear();
        isWrightingUsername = true;
    }

    void Draw()
    {
        DrawBorder();
        DrawText();
    }

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


    void SetCursor()
    {
        move(
            getbegy(win) + 1 + !isWrightingUsername, 
            getbegx(win) + 10 + (isWrightingUsername ? hashUsername.size() : hashPassword.size()));
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