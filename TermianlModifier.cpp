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
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD dwMode = 0;
            GetConsoleMode(hOut, &dwMode);
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
    }
    #endif
   void TerminalModifier:: terminalSleep(int numberOfSeconds){
        this_thread::sleep_for(chrono::seconds(numberOfSeconds));
    }
    void TerminalModifier:: gotoxy(int x, int y) {
        cout << "\033[" << y << ";" << x << "H" << std::flush;
    }






