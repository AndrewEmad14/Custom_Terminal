#include "TerminalModifier.h"
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

    TerminalModifier::TerminalModifier(){
        #ifdef _WIN32
          enableAnsiSupport();
        #endif

    }


    void TerminalModifier:: enableAnsiSupport() {
        #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);                    // Get handle to the console's standard output buffer
        DWORD dwMode = 0;                                                 // Declare variable to hold current console mode flags
        GetConsoleMode(hOut, &dwMode);                                    // Retrieve current console output mode settings
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;                     // Enable support for ANSI/VT100 escape sequences (e.g., colored text)
        SetConsoleMode(hOut, dwMode);                                     // Apply the updated mode to the console output buffer
        #endif
    }

    void TerminalModifier:: terminalSleep(int numberOfSeconds){
        this_thread::sleep_for(chrono::seconds(numberOfSeconds));
    }
    void TerminalModifier:: gotoxy(int x, int y) {
        cout << "\033[" << y << ";" << x << "H" << std::flush;
    }

    void TerminalModifier::  displayText(string color,string text,int postionX,int postionY){
        gotoxy(postionX,postionY);
        paintText(color,text);

    }
    void TerminalModifier::  clearScreen(){
            cout<<CLEAR_SCREEN<<flush;
    }
    void TerminalModifier::  paintText(string color,string text){
            cout<<color<<text<<RESET_COLOR<<std::flush;
    }


                                                                                        //to be classed
    void TerminalModifier::getTerminalSize(int& width, int& height) {
        #ifdef _WIN32
          CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        width = w.ws_col;
        height = w.ws_row;
        #endif // _WIN32

    }
