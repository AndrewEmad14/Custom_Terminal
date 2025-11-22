#ifndef VI_EDITOR
#define VI_EDITOR
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include "Keyboard.h"
#include "TerminalModifier.h"
using namespace std;
// fgets(YourString,the size of said string,inputStream) puts the input stream inside your string
// fputs(CString,fileName) puts your CString in the file
// fopen(file name,"a") OPENS FILE IN A MODE
//r"	read: Open file for input operations. The file must exist.
//"w"	write: Create an empty file for output operations. If a file with the same name already exists, its contents are discarded and the file is treated as a new empty file.
//"a"	append: Open file for output at the end of a file. Output operations always write data at the end of the file, expanding it. Repositioning operations (fseek, fsetpos, rewind) are ignored. The file is created if it does not exist.
//"r+"	read/update: Open a file for update (both for input and output). The file must exist.
//"w+"	write/update: Create an empty file and open it for update (both for input and output). If a file with the same name already exists its contents are discarded and the file is treated as a new empty file.
//"a+"	append/update: Open a file for update (both for input and output) with all output operations writing data at the end of the file. Repositioning operations (fseek, fsetpos, rewind) affects the next input operations, but output operations move the position back to the end of file. The file is created if it does not exist.
typedef enum {
    READ_OK,           // Successfully read complete line
    READ_OVERFLOW,    // Line too long, overflow
    READ_EOF,          // End of file
    READ_ERROR         // Read error
} ReadStatus;

class ViEditor{

public:

// Function to clear the input buffer
void clearInputBuffer();

ReadStatus readLine( char *buffer, long cStringSize);



bool saveToFile(char * sentence);

void enterVI();
bool displayFile();

char* takeInput(TerminalModifier &myTerm,Keyboard &myKeyboard);
};



#endif // VI_EDITOR
