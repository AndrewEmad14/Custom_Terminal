#include"ViEditor.h"
#include "Keyboard.h"
#include "TerminalModifier.h"
void ViEditor:: clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

ReadStatus ViEditor::readLine( char *buffer, long cStringSize) {
    if (fgets(buffer, cStringSize, stdin) == NULL) {
        return READ_EOF;
    }

    size_t len = strlen(buffer);

                                       // Check if line was complete
    if (len > 0 && buffer[len - 1] == '\n') {

        return READ_OK;
    }


                                    // Line was too long
    if (len == cStringSize - 1) {
        clearInputBuffer();
        return READ_OVERFLOW;
    }

   return READ_EOF;
}
bool  ViEditor::  saveToFile(char * sentence){
    FILE * pFile;
    pFile = fopen ("mylog.txt","a");
    fputs (sentence,pFile);
    fclose (pFile);
    return true;
}

bool ViEditor::displayFile(){
    FILE * pFile;
    long inputSize;                        // we use long int because ftell returns long
    size_t result;                         //we use size_t because fread returns size_t

    pFile = fopen("mylog.txt","r");
    if (pFile==NULL) {
            fputs ("File error",stderr);
            return false;
    }
                                    // obtain file size:
    fseek(pFile, 0, SEEK_END);   // Move file pointer to the end of the file
    inputSize = ftell(pFile);        // Get the current position (which is the file size in bytes)
    rewind(pFile);               // Move file pointer back to the beginning of the file

                                                        // allocate memory to contain the whole file:
    char* buffer;
    buffer = (char*) malloc (sizeof(char)*inputSize);
    if (buffer == NULL) {
            fputs ("Memory error",stderr);
            false;
    }


                                                        // copy the file into the buffer:
    result = fread (buffer,1,inputSize,pFile);
    if (result != inputSize) {
            fputs ("Reading error",stderr);
            return false;
    }

    puts(buffer);

    fclose (pFile);

    free (buffer);
    return true;
}

char* ViEditor:: takeInput(TerminalModifier &myTerm,Keyboard &myKeyboard){


    char *sentence ;
    long cStringSize;
    bool exitFlag=false;
    int cursorPos = 0;
    int textLength = 0;
    bool isInsertMode = true;
    printf("please enter the size of the string:");
    while (!(cin >> cStringSize)) {
                            // Handle error
        cin.clear();        //  RESET failbit (and other flags)
        clearInputBuffer();
        cout << "Invalid number!\n";
    }
    cin.ignore();                           //buffer problems
    cStringSize+=1;                      //for null terminator and for new line
    sentence = (char*) malloc(sizeof(char) * cStringSize);
    myTerm.clearScreen();
    myKeyboard.enableRawMode();
     while (!exitFlag) {
        int key = myKeyboard.readKey();


            if (key == KEY_ESC_CODE || key == KEY_ENTER_CODE) {
                 exitFlag=true;

            }else if (key >= 32 && key <= 126) {
                if (textLength < cStringSize - 2) {
                    sentence[cursorPos] = (char)key;
                    cursorPos++;
                    textLength++;
                    sentence[textLength] = '\0';

                    // USE write() instead of printf() for immediate output
                    char c = (char)key;
                    write(STDOUT_FILENO, &c, 1);
                } else {
                    write(STDOUT_FILENO, "\a", 1);  // Beep
                }

            }else if (key == KEY_BACKSPACE_CODE) {
                if (cursorPos > 0) {
                    for (int i = cursorPos - 1; i < textLength; i++) {
                        sentence[i] = sentence[i + 1];
                    }
                    cursorPos--;
                    textLength--;
                     myTerm.clearScreen();
                     write(STDOUT_FILENO, sentence, strlen(sentence));
                }

            }else   if (key == KEY_LEFT_CODE) {
                // Move cursor left
                if (cursorPos > 0) {
                    cursorPos--;
                    write(STDOUT_FILENO, "\b", 1);  // Just move cursor back
                }

            } else if (key == KEY_RIGHT_CODE) {
                // Move cursor right
                if (cursorPos < textLength) {
                    cursorPos++;
                    write(STDOUT_FILENO, "\033[C", 3);  // Move cursor forward
                }

            }



    }

    myKeyboard.disableRawMode();
    return sentence;

}
