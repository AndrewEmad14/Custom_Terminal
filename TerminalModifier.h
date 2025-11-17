                                                            //\033 is the octal representation for ESC
                                                            //[ starts control sequence
                                                            //h is cursor postion
                                                            //text style and color
#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h> // for timeout
#include <errno.h>
using namespace std;
#ifndef TERMINAL_MODIFIER_H
#define TERMINAL_MODIFIER_H
                                                    //EXTENDED KEYS LINUX VERSION
#define KEY_UNKNOWN -1

// Standard ASCII control characters
#define KEY_LBRACKET  91
#define KEY_ESC        '\033'
#define KEY_ENTER      '\n'
#define KEY_BACKSPACE  '\177'
#define KEY_LBRACKET   '['          // ASCII '[' is 91, but use char literal

// Arrow key identifiers (characters after ESC [ )


                            // Printable ASCII: 32 (space) to 126 (~)
                            // So we reserve special keys above 255
#define KEY_SPECIAL_START 1000
#define KEY_UP      1000
#define KEY_DOWN    1001
#define KEY_LEFT    1002
#define KEY_RIGHT   1003
#define KEY_HOME    1004
#define KEY_END     1005
#define KEY_DELETE  1006
#define KEY_INSERT  1007


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

#endif


class TerminalModifier{


        void enableAnsiSupport(void);
        void gotoxy(int x, int y);
        void paintText(string color,string text);
        int readWithTimeout(char* c, int timeout_ms);

        public:

        TerminalModifier();
        void terminalSleep(int numberOfSeconds);
        void clearScreen(void);
        void DisplayText(string color,string text,int postionX,int postionY);
        void enableRawMode(void);
        void disableRawMode(void);
        int readKey();

};




