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
    #ifdef _WIN32
    #else
    termios TerminalModifier::orig_termios;
    #endif // _WIN32

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

    void TerminalModifier::  displayText(string color,string text,int postionX,int postionY){
        gotoxy(postionX,postionY);
        paintText(color,text);

    }
    void TerminalModifier::  clearScreen(){
            cout<<CLEAR_SCREEN;
    }
    void TerminalModifier::  paintText(string color,string text){
            cout<<color<<text<<RESET_COLOR<<std::flush;
    }
    string TerminalModifier:: getRandColor(){
        int randomNumber=rand()%6;


                switch (randomNumber) {
                    case 0: return RESET_COLOR;
                    case 1: return RED_COLOR;
                    case 2: return GREEN_COLOR;
                    case 3: return YELLOW_COLOR;
                    case 4: return BLUE_COLOR;
                    case 5: return MAGENTA_COLOR;
                    case 6: return CYAN_COLOR;
                    default: return "";  // no color
                }



    }
                                                                                        //to be classed
    void TerminalModifier:: enableRawMode() {
        #ifdef _WIN32

        #else
         tcgetattr(STDIN_FILENO, &orig_termios);
            termios raw = orig_termios;
            raw.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode & echo
            raw.c_cc[VMIN] = 0;  // Minimum number of characters to read
            raw.c_cc[VTIME] = 0; // Timeout in deciseconds (0 = no timeout)
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        #endif
    }

    void TerminalModifier:: disableRawMode() {
        #ifdef _WIN32

        #else
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
        #endif // _WIN32
    }

    // Helper: read one char with optional timeout (in milliseconds)
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
 int TerminalModifier:: readWithTimeout(char* c, int timeout_ms) {
     #ifdef _WIN32

    #else
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
    #endif
}

#ifdef _WIN32

int  TerminalModifier::readKey() {
    int ch = _getch();

    if (ch == EXTENDED_WIN) {

        int ext = _getch();
        switch (ext) {
            case KEY_UP_WIN : return KEY_UP_CODE;
            case KEY_DOWN_WIN : return KEY_DOWN_CODE;
            case KEY_LEFT_WIN : return KEY_LEFT_CODE;
            case KEY_RIGHT_WIN : return KEY_RIGHT_CODE;

        }
    }

    if (ch == KEY_ESC_WIN ) return KEY_ESC_CODE;
    if (ch == KEY_ENTER_WIN ) return KEY_ENTER_CODE;      // Enter
    if (ch == KEY_BACKSPACE_WIN  || ch == KEY_BACKSPACE_ALT_WIN ) return KEY_BACKSPACE_CODE;


}
#else

  int TerminalModifier::readKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) <= 0) return KEY_UNKNOWN;

    if (c == KEY_ESC) {
        char second = 0, third = 0;
        // Try to read next char within ~50ms (typical for escape sequences)
        if (readWithTimeout(&second, 50) > 0) {
            if (second == KEY_LBRACKET) {
                if (readWithTimeout(&third, 50) > 0) {
                    switch (third) {
                        case KEY_UP:  return KEY_UP_CODE;
                        case KEY_DOWN: return KEY_DOWN_CODE;
                        case KEY_RIGHT:return KEY_RIGHT_CODE;
                        case KEY_LEFT: return KEY_LEFT_CODE;
                        default:       return KEY_UNKNOWN;
                    }
                }
                return KEY_UNKNOWN; //  third char timeout
            }
            return KEY_UNKNOWN; //  second char wasn't '['
        } else {
            // No more input within timeout → it's a standalone ESC
            return KEY_ESC_CODE;
        }
    } else {
        switch (c) {
            case KEY_ENTER:
            case KEY_ENTER_ALT: return KEY_ENTER_CODE;
            case KEY_BACKSPACE: return KEY_BACKSPACE_CODE;
            default:            return KEY_UNKNOWN;
        }
    }
}
#endif
