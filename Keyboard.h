#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<iostream>
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
 #ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <sys/ioctl.h>// Provides the ioctl() function for device-specific input/output operations (e.g., terminal control, window size)
    #include <unistd.h> // Declares standard POSIX system calls like read(), write(), close(), and access to file descriptors (e.g., STDIN_FILENO)
    #include <sys/select.h> // Enables the select() system call for monitoring multiple file descriptors for I/O readiness (useful for non-blocking I/O)
#endif
                                                //unified key codes


#define KEY_UP_CODE      1000
#define KEY_DOWN_CODE    1001
#define KEY_LEFT_CODE    1002
#define KEY_RIGHT_CODE   1003
#define KEY_ENTER_CODE   1004
#define KEY_ESC_CODE     1005
#define KEY_BACKSPACE_CODE 1006

class Keyboard{
        int readWithTimeout(char* c, int timeout_ms);
    public:
        #ifdef _WIN32
        #else
            static termios orig_termios;
        #endif // _WIN32
        void enableRawMode(void);
        void disableRawMode(void);
        int readKey();



};





#endif
