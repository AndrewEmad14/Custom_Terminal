#include <iostream>
#include "TerminalModifier.h"
#define DEFAULT_VAL 0
#define STARTNUM 1
#define STARTROW 0
#define PADDING 5
#define OFFSET 10
#define DEFAULT_STRING_VAL ""
using namespace std;


int main(void) {
    TerminalModifier myTerm;


    int magicBox=DEFAULT_VAL;
    cin>>magicBox;
    int num = STARTNUM;
    int row = STARTROW;                  // Start at top row
    int col = magicBox / 2;              // Middle column
    string currentColor = DEFAULT_STRING_VAL;

    while (num <= magicBox * magicBox) {

                                                                                    //print the number
         //cout<<"row: "<<row<<"col: "<<col<<endl;

        myTerm.terminalSleep(1);
        currentColor=myTerm.getRandColor();
        myTerm.displayText(currentColor,to_string(num),(row+1)*10,(col+1)*5);
                                                        // If next cell is already filled, move down instead
        if (num%magicBox==0) {
            row = (row + 1) % magicBox;                 // Move down from original position
                                                        // col stays the same
        } else {
            row = (row - 1 + magicBox) % magicBox; // Move up (with wrap)
            col = (col + 1) % magicBox;             // Move right (with wrap)
        }


       num++;
    }
    int width=DEFAULT_VAL,height=DEFAULT_VAL;

    myTerm.getTerminalSize(width,height);
    currentColor=myTerm.getRandColor();
    myTerm.displayText(currentColor,"",width+1,height);



    return 0;
}
