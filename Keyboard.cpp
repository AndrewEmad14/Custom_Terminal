#include "Keyboard.h"
#ifdef _WIN32
#else
    termios Keyboard::orig_termios;
#endif // _WIN32
 void Keyboard:: enableRawMode() {
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

    void Keyboard:: disableRawMode() {
        #ifdef _WIN32

        #else
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
        #endif // _WIN32
    }

    // Helper: read one char with optional timeout (in milliseconds)

 int Keyboard:: readWithTimeout(char* c, int timeout_ms) {
     #ifdef _WIN32

    #else
            // Declare a file descriptor set to monitor input readiness
            fd_set readfds;
            // Clear the set to ensure it starts empty (required before use)
            FD_ZERO(&readfds);
            // Add standard input (keyboard) to the set so we can check if a key was pressed
            FD_SET(STDIN_FILENO, &readfds);

            // Prepare a timeout value for the select() call
            struct timeval timeout;
            // Convert timeout from milliseconds to seconds (e.g., 1500 ms → 1 sec)
            timeout.tv_sec = timeout_ms / 1000;
            // Convert the remaining milliseconds to microseconds (e.g., 500 ms → 500,000 µs)
            timeout.tv_usec = (timeout_ms % 1000) * 1000;

            // Wait up to 'timeout' for data to become available on stdin (or any fd in readfds)
            // STDIN_FILENO + 1 = 1 (select() needs the highest fd + 1)
            // We only care about reading (not writing or errors), so other fd sets are nullptr
            // Returns: >0 if data is ready, 0 on timeout, -1 on error
            int ready = select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout);

            // If data is ready (user pressed a key), read one byte from stdin
            if (ready > 0) {
                // Read a single byte into buffer 'c' (caller must ensure c points to valid memory)
                // In raw mode, this captures one part of a keypress (e.g., 'A', or ESC for special keys)
                return read(STDIN_FILENO, c, 1);
            }
            // If timeout occurred or an error happened, return 0 to indicate "no key pressed"
            return 0; // timeout or error
    #endif
}

#ifdef _WIN32

int  Keyboard::readKey() {
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

  int Keyboard::readKey() {
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
