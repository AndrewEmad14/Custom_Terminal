#include "TerminalModifier.h"
#include <thread>
#include <chrono>
#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#endif
using namespace std;

    TerminalModifier::TerminalModifier(){
        #ifdef _WIN32
            enableAnsiSupport();
        #endif

    }
    #ifdef _WIN32
    void enableAnsiSupport() {
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// Gets a handle to the standard output device (usually the console screen). This handle is used to interact with the console output.
            DWORD dwMode = 0;// Declares a variable to store the current console mode flags. DWORD is a 32-bit unsigned integer type commonly used in Windows API.
            GetConsoleMode(hOut, &dwMode);// Retrieves the current console mode settings for the output handle and stores them in dwMode. This gets the existing configuration flags.
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;// Adds the ENABLE_VIRTUAL_TERMINAL_PROCESSING flag to the existing mode using bitwise OR. This flag enables ANSI escape sequence processing, allowing you to use color codes and cursor positioning sequences (like \033[31m for red text).
            SetConsoleMode(hOut, dwMode);// Applies the modified mode settings back to the console. This activates the changes, enabling virtual terminal sequences for that console session.
    }
    #endif
   void TerminalModifier:: terminalSleep(int numberOfSeconds){
        this_thread::sleep_for(chrono::seconds(numberOfSeconds));
    }
    void TerminalModifier:: gotoxy(int x, int y) {
        cout << "\033[" << y << ";" << x << "H" << std::flush;
    }






