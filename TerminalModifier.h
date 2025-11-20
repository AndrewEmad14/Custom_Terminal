                                                            //\033 is the octal representation for ESC
                                                            //[ starts control sequence
                                                            //h is cursor postion
                                                            //text style and color
#include <string>
#include <iostream>

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

        public:

        TerminalModifier();
        void terminalSleep(int numberOfSeconds);
        void clearScreen(void);
        void displayText(string color,string text,int postionX,int postionY);
        void getTerminalSize(int& width, int& height);
        void gotoxy(int x, int y);


};

#endif



