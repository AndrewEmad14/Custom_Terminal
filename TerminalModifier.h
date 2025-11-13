                                //\033 is the octal representation for ESC
                                //[ starts control sequence
                                //h is cursor postion
                                //text style and color
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

// clear the screen and reset the cursor Postion to the top left of the treminal
#define CLEAR_SCREEN  "\033[2J\033[H"

#endif // TERMINAL_MODIFIER_H


class TerminalModifier{
        #ifdef _WIN32
        TerminalModifier(){
                       void enableAnsiSupport(void);

        }
        #endif
        public:

        TerminalModifier();
        void terminalSleep(int numberOfSeconds);
        void gotoxy(int x, int y);
};




