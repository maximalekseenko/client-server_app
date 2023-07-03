#pragma once



// buildin libraries
#include <ncurses.h>
#include <string>
#include <pthread.h>
#include <vector>



namespace window
{
    /// @brief Custom virtual struct for curses.h's windows.
    struct Window
    {
        /// @brief Standart ncurses.h window. Initialize in constructor. 
        WINDOW* win;

        /// @brief Called when this window becomes current window.
        virtual void OnOpen(){}
        /// @brief Called when this window stops to be current window.
        virtual void OnClose(){}

        /// @brief Called when this window needs to be drawn.
        virtual void Draw(){}
        /// @brief Called after drawing to fix cursor position for user input.
        virtual void SetCursor(){}


        /// @brief Called when user makes "Select" action (e.g. by pressing Enter).
        virtual void ActionSelect(){}
        /// @brief Called when user makes "Cancel" action (e.g. by pressing Esc, then Esc).
        virtual void ActionCancel(){}
        /// @brief Called when user makes "Up" action (e.g. by pressing Arrow Up).
        virtual void ActionUp(){}
        /// @brief Called when user makes "Down" action (e.g. by pressing Arrow Down).
        virtual void ActionDown(){}
        /// @brief Called when user makes "Left" action (e.g. by pressing Arrow Left).
        virtual void ActionLeft(){}
        /// @brief Called when user makes "Right" action (e.g. by pressing Arrow Right).
        virtual void ActionRight(){}
        /** @brief Called when user makes "Char" action (e.g. by pressing any letter, number or backspace).
         * 
         * @param ch Character of bressed button. Character for backspace is '\b'.
         */
        virtual void ActionChar(char ch){}
    };

    /// @brief Array containing instaces of all windows in program. Initializes in window::Init().
    static std::vector<Window*> Windows;
    /// @brief Id of current window in window::Windows array.
    static int currentWindowId = 0;

    /// @brief Get the current Window object.
    static Window* GetCurrentWindow();

    /// @brief Thread object for running window::MainThread;
    static pthread_t mainThread;

    static std::string errorText;

    /// @brief MUST be called before use of this module.
    void Init();

    /// @brief Starts window::MainThread.
    void Run();

    /// @brief Main Thread with logic. Used by window::Run().
    void* MainThread(void* args);

    /// @brief Get the User Input.
    void GetUserInput();

    /// @brief Draws current window to console.
    void Draw();

    /** @brief Change current window.
     * 
     * @param __winID id of a new current window from window::Windows array.
     */
    void OpenWindow(int __winID);
}