#include <iostream>
#include "TerminalModifier.h"
#define DEFAULT_VAL 0
#define MENU_WIDTH 18
#define NUMBER_OF_BUTTONS 3
using namespace std;

void setBtnColor(int &current,string buttons[]);
void  printMenu(string firstBtn,string secondBtn,string thridBtn,int startX,int startY);

void printMenu(TerminalModifier& myTerm,string firstBtn,string secondBtn,string thridBtn,int startX,int startY){
                myTerm.displayText(firstBtn, "╔════════════════╗", startX, startY);
                myTerm.displayText(firstBtn, "║      New       ║", startX, startY + 1);
                myTerm.displayText(firstBtn, "╚════════════════╝", startX, startY + 2);

                                                                                    // Second button (1 blank line gap)
                myTerm.displayText(secondBtn, "╔════════════════╗", startX, startY + 4);
                myTerm.displayText(secondBtn, "║    Display     ║", startX, startY + 5);
                myTerm.displayText(secondBtn, "╚════════════════╝", startX, startY + 6);

                                                                            // Third button (1 blank line gap)
                myTerm.displayText(thridBtn, "╔════════════════╗", startX, startY + 8);
                myTerm.displayText(thridBtn, "║      Exit      ║", startX, startY + 9);
                myTerm.displayText(thridBtn, "╚════════════════╝", startX, startY + 10);



}
void setBtnColor(int &current,string buttons[]){
    if(current<0)
        current=NUMBER_OF_BUTTONS-1;
    else if (current > NUMBER_OF_BUTTONS-1)
        current=0;

    for(int i=0;i<NUMBER_OF_BUTTONS;i++){
    if(i==current)
        buttons[i]=BLUE_COLOR;
    else
        buttons[i]=RESET_COLOR;
    }
}
int main(void) {
    TerminalModifier myTerm;
    myTerm.enableRawMode();
    int terminalWidth=DEFAULT_VAL,terminalHeight=DEFAULT_VAL;
    myTerm.getTerminalSize(terminalWidth,terminalHeight);
    int menuWidth = MENU_WIDTH;
    int startX = (terminalWidth - menuWidth) / 2;
    int startY = terminalHeight / 2 - 3;  // Center vertically (menu is 7 lines tall)
    int current = 0;
    bool exit =false,insidePage=false;
    string buttons[NUMBER_OF_BUTTONS];
    setBtnColor(current,buttons);

    printMenu( myTerm,buttons[0], buttons[1],buttons[2],startX,startY);

    while (true) {

                  int key=myTerm.readKey() ;                                                 // First button
                 switch (key) {
                        case KEY_UP_CODE:
                            current--;

                            setBtnColor(current,buttons);

                            printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            break;

                        case KEY_DOWN_CODE:

                              current++;
                            setBtnColor(current,buttons);
                            printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            break;

                        case KEY_RIGHT_CODE:
                            current--;
                            setBtnColor(current,buttons);
                            printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            break;

                        case KEY_LEFT_CODE:
                            current++;
                            setBtnColor(current,buttons);
                            printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            break;

                        case KEY_ESC_CODE:
                            exit=true;
                            break;

                        case KEY_ENTER_CODE:
                                    cout << "\nDEBUG: Enter pressed! current=" << current << endl;
                                    if(current==2) {
                                        cout << "DEBUG: Exiting..." << endl;
                                        exit=true;
                                    }
                                    else {
                                        cout << "DEBUG: Going to page " << current << endl;
                                        insidePage=true;
                                        myTerm.clearScreen();
                                        cout << flush;
                                    }
                                    break;

                        case KEY_BACKSPACE_CODE:
                            if(insidePage){
                                setBtnColor(current,buttons);
                                printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            }

                            break;


                    }
                    if(exit)
                        break;


    }
    myTerm.clearScreen();


    myTerm.disableRawMode();
    return 0;
}
