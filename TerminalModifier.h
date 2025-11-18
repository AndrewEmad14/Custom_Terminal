                                                            //\033 is the octal representation for ESC
                                                            //[ starts control sequence
                                                            //h is cursor postion
                                                            //text style and color
#include <string>
#include <iostream>
#include <cstdlib>
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <sys/select.h>
    #include <errno.h>
#endif

using namespace std;
#ifndef TERMINAL_MODIFIER_H
#define TERMINAL_MODIFIER_H
#define KEY_UNKNOWN -1
#ifdef _WIN32
    #define EXTENDED_WIN        0xE0
    #define KEY_UP_WIN          72
    #define KEY_DOWN_WIN        80
    #define KEY_LEFT_WIN        75
    #define KEY_RIGHT_WIN       77
    #define KEY_ENTER_WIN       13
    #define KEY_BACKSPACE_WIN   8
    #define KEY_BACKSPACE_ALT_WIN 127
    #define KEY_ESC_WIN        27
#else
    #define KEY_ESC        '\033'
    #define KEY_ENTER      '\n'
    #define KEY_ENTER_ALT  '\r'
    #define KEY_BACKSPACE  '\177'
    #define KEY_LBRACKET   '['
    #define KEY_UP         'A'
    #define KEY_DOWN       'B'
    #define KEY_RIGHT      'C'
    #define KEY_LEFT       'D'
#endif
                                                //unified key codes


#define KEY_UP_CODE      1000
#define KEY_DOWN_CODE    1001
#define KEY_LEFT_CODE    1002
#define KEY_RIGHT_CODE   1003
#define KEY_ENTER_CODE   1004
#define KEY_ESC_CODE     1005
#define KEY_BACKSPACE_CODE 1006

                                                    // ANSI color macros
#define BLACK_COLOR   "\033[30m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"
#define YELLOW_COLOR  "\033[33m"
#define BLUE_COLOR    "\033[34m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR    "\033[36m"
#define BOLD          "\033[1m"
#define ITALIC        "\033[3m"
#define RESET_COLOR     "\033[0m"

                                                            // clear the screen and reset the cursor Postion
                                                            // to the top left of the Terminal
#define CLEAR_SCREEN  "\033[2J\033[H"



class TerminalModifier{


        void enableAnsiSupport(void);

        void paintText(string color,string text);
        int readWithTimeout(char* c, int timeout_ms);
         void gotoxy(int x, int y);
        public:
        #ifdef _WIN32
        #else
            static termios orig_termios;
        #endif // _WIN32
        TerminalModifier();
        void terminalSleep(int numberOfSeconds);
        void clearScreen(void);
        void displayText(string color,string text,int postionX,int postionY);
        void enableRawMode(void);
        void disableRawMode(void);
        int readKey();

        void getTerminalSize(int& width, int& height);
        string getRandColor();


};

#endif



