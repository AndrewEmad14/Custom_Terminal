#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h> // for timeout
#include <errno.h>

#define KEY_ESC        '\033'
#define KEY_ENTER      '\n'
#define KEY_BACKSPACE  '\177'
#define KEY_LBRACKET   '['          // ASCII '[' is 91, but use char literal

// Arrow key identifiers (characters after ESC [ )
#define KEY_UP         'A'
#define KEY_DOWN       'B'
#define KEY_RIGHT      'C'
#define KEY_LEFT       'D'

using namespace std;

void enableRawMode() {
    termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode & echo
    raw.c_cc[VMIN] = 0;  // Minimum number of characters to read
    raw.c_cc[VTIME] = 0; // Timeout in deciseconds (0 = no timeout)
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
    termios orig_termios;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// Helper: read one char with optional timeout (in milliseconds)
int readWithTimeout(char* c, int timeout_ms) {
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

int main(void) {

    enableRawMode();

    cout << "Press keys (ESC to exit loop manually if needed)...\n";

    while (1) {
        char c;
        if (read(STDIN_FILENO, &c, 1) <= 0) continue;

        if (c == KEY_ESC) {
            char second = 0, third = 0;

            // Try to read next char within ~50ms (typical for escape sequences)
            if (readWithTimeout(&second, 50) > 0) {
                if (second == KEY_LBRACKET) {
                    if (readWithTimeout(&third, 50) > 0) {
                        switch (third) {
                            case KEY_UP:    cout << "Up arrow\n"; break;
                            case KEY_DOWN:  cout << "Down arrow\n"; break;
                            case KEY_RIGHT: cout << "Right arrow\n"; break;
                            case KEY_LEFT:  cout << "Left arrow\n"; break;
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
                case 'q': case 'Q':
                    cout << "Quitting...\n";
                    goto cleanup; // or break with flag
                default:
                    cout << "Other key: '" << c << "' (code " << (int)(unsigned char)c << ")\n";
                    break;
            }
        }
    }

cleanup:
    disableRawMode();
    return 0;
}
