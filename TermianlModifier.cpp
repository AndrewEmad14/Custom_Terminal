#include "TerminalModifier.h"
#include <thread>
#include <chrono>
#include <iostream>
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <ncurses.h>
#endif
using namespace std;

    TerminalModifier::TerminalModifier(){
        #ifdef _WIN32
          enableAnsiSupport();
        #endif

    }
    void TerminalModifier:: enableAnsiSupport() {
        #ifdef _WIN32
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD dwMode = 0;
            GetConsoleMode(hOut, &dwMode);
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        #endif
    }
    void TerminalModifier:: terminalSleep(int numberOfSeconds){
        this_thread::sleep_for(chrono::seconds(numberOfSeconds));
    }
    void TerminalModifier:: gotoxy(int x, int y) {
        cout << "\033[" << y << ";" << x << "H" << std::flush;
    }

    void TerminalModifier::  DisplayText(string color,string text,int postionX,int postionY){
        gotoxy(postionX,postionY);
        paintText(color,text);

    }
    void TerminalModifier::  clearScreen(){
            cout<<CLEAR_SCREEN;
    }
    void TerminalModifier::  paintText(string color,string text){
            cout<<color<<text<<RESET_COLOR<<std::flush;
    }
    void TerminalModifier:: enableRawMode() {
     termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode & echo
    raw.c_cc[VMIN] = 0;  // Minimum number of characters to read
    raw.c_cc[VTIME] = 0; // Timeout in deciseconds (0 = no timeout)
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

    void TerminalModifier:: disableRawMode() {
       termios orig_termios;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }

    // Helper: read one char with optional timeout (in milliseconds)
    int TerminalModifier:: readWithTimeout(char* c, int timeout_ms) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval timeout;
        timeout.tv_sec = timeout_ms / 1000;
        timeout.tv_usec = (timeout_ms % 1000) * 1000;

        int ready = select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout);
        if (ready > 0) {
            return read(STDIN_FILENO, c, 1);
        }
        return 0; // timeout or error
    }



    int TerminalModifier::readKey() {
        char c;
        if (read(STDIN_FILENO, &c, 1) <= 0) return -1;

        if (c == KEY_ESC) {
            char second = 0, third = 0;

            // Try to read next char within ~50ms (typical for escape sequences)
            if (readWithTimeout(&second, 50) > 0) {
                if (second == KEY_LBRACKET) {
                    if (readWithTimeout(&third, 50) > 0) {
                        switch (third) {
                            case 'A': return KEY_UP;
                            case 'B': return KEY_DOWN;
                            case 'C': return KEY_RIGHT;
                            case 'D': return KEY_LEFT;
                            case 'H': return KEY_HOME;
                            case 'F': return KEY_END;
                            default:        cout << "Unknown escape seq: ESC [" << third << "\n"; break;
                        }
                    } else {
                        cout << "ESC [ (incomplete)\n";
                    }
                } else {
                    cout << "ESC followed by: " << second << "\n";
                }
            } else {
                // No more input within timeout → it's a standalone ESC
                cout << "ESCAPE\n";
            }
        } else {
            switch (c) {
                case KEY_ENTER:    cout << "Enter\n"; break;
                case KEY_BACKSPACE: cout << "Backspace\n"; break;
                default:
                    cout << "Other key: '" << c << "' (code " << (int)(unsigned char)c << ")\n";
                    return KEY_UNKNOWN;
            }
        }
}

