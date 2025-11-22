#include <iostream>
#include "TerminalModifier.h"
#include "Keyboard.h"
#include "ViEditor.h"
#define DEFAULT_VAL 0
#define MENU_WIDTH 18
#define NUMBER_OF_BUTTONS 3
using namespace std;

void setBtnColor(int &current,string buttons[]);
void  printMenu(string firstBtn,string secondBtn,string thridBtn,int startX,int startY);
void  enterInsertMode(ViEditor & myViEditor,Keyboard & myKeyboard);
bool displayOutput(ViEditor & myViEditor);
void enterCommandMode(ViEditor & myViEditor);
void printMenu(TerminalModifier& myTerm,string firstBtn,string secondBtn,string thridBtn,int startX,int startY){
                myTerm.displayText(firstBtn, "+----------------+", startX, startY);
                myTerm.displayText(firstBtn, "|      New       |", startX, startY + 1);
                myTerm.displayText(firstBtn, "+----------------+", startX, startY + 2);
                                                                                                // Second button (1 blank line gap)
                myTerm.displayText(secondBtn, "+----------------+", startX, startY + 4);
                myTerm.displayText(secondBtn, "|    Display     |", startX, startY + 5);
                myTerm.displayText(secondBtn, "+----------------+", startX, startY + 6);
                                                                                        // Third button (1 blank line gap)
                myTerm.displayText(thridBtn, "+----------------+", startX, startY + 8);
                myTerm.displayText(thridBtn, "|      Exit      |", startX, startY + 9);
                myTerm.displayText(thridBtn, "+----------------+", startX, startY + 10);



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
void  enterInsertMode(ViEditor & myViEditor,Keyboard & myKeyboard,TerminalModifier &myTerm){
    myKeyboard.disableRawMode();
    char* sentence = myViEditor.takeInput(myTerm,myKeyboard);
    //do you wish to save

    myViEditor.saveToFile(sentence);

    return;
    //enter if you want to continue appending text esc if you want to exit


}
void enterCommandMode(Keyboard & myKeyboard){
     myKeyboard.enableRawMode();
}

bool displayOutput(ViEditor & myViEditor){
    myViEditor.displayFile();
    //press enter to continue
    return true;


}
int main(void) {
    TerminalModifier myTerm;

    Keyboard myKeyboard;

    ViEditor myViEditor;

    myKeyboard.enableRawMode();

    int terminalWidth=DEFAULT_VAL,terminalHeight=DEFAULT_VAL;

    myTerm.getTerminalSize(terminalWidth,terminalHeight);
    int menuWidth = MENU_WIDTH;
    int startX = (terminalWidth - menuWidth) / 2;
    int startY = terminalHeight / 2 - 3;  // Center vertically (menu is 7 lines tall)

    int currentBtn = 0;
    bool exit =false,insidePage=false;

    string buttons[NUMBER_OF_BUTTONS];
    setBtnColor(currentBtn,buttons);

    printMenu( myTerm,buttons[0], buttons[1],buttons[2],startX,startY);

    while (!exit) {

                  int key=myKeyboard.readKey() ;
                 switch (key) {
                        case KEY_UP_CODE:
                            currentBtn--;
                            setBtnColor(currentBtn,buttons);
                            printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            break;

                        case KEY_DOWN_CODE:

                            currentBtn++;
                            setBtnColor(currentBtn,buttons);
                            printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            break;

                        case KEY_RIGHT_CODE:
                            currentBtn--;
                            setBtnColor(currentBtn,buttons);
                            printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            break;

                        case KEY_LEFT_CODE:
                            currentBtn++;
                            setBtnColor(currentBtn,buttons);
                            printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            break;

                        case KEY_ESC_CODE:
                            exit=true;
                            break;

                        case KEY_ENTER_CODE:
                                    if(currentBtn==0){
                                        insidePage=true;
                                        myTerm.clearScreen();

                                        enterInsertMode(myViEditor,myKeyboard,myTerm);
                                        myKeyboard.enableRawMode();
                                        myTerm.clearScreen();

                                    printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);

                                    }else if(currentBtn==1) {
                                        myTerm.clearScreen();
                                        insidePage=true;
                                        myKeyboard.disableRawMode();
                                        displayOutput(myViEditor);
                                        myKeyboard.enableRawMode();




                                    }
                                    else {
                                        exit=true;
                                    }




                            break;
                        case KEY_BACKSPACE_CODE:
                            if(insidePage){
                                myTerm.clearScreen();
                                setBtnColor(currentBtn,buttons);
                                printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);
                            }
                        default:
                            ;



                    }



    }
    myTerm.clearScreen();


    myKeyboard.disableRawMode();
    return 0;
}
