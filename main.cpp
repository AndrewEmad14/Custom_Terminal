#include <iostream>
#include "TerminalModifier.h"
#include "Keyboard.h"
#include "Employee.h"
#define DEFAULT_VAL 0
#define MENU_WIDTH 18
#define NUMBER_OF_BUTTONS 3
using namespace std;

void setBtnColor(int &current,string buttons[]);
void  printMenu(string firstBtn,string secondBtn,string thridBtn,int startX,int startY);
void generateEmployee(TerminalModifier& myTerm);

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

void generateEmployee(TerminalModifier& myTerm,Keyboard& myKeyboard,Employee e[],int* current){
    while(true){
        myTerm.terminalSleep(1);
        int key=myKeyboard.readKey();
        switch(key){
                case KEY_ENTER_CODE:
                    myTerm.clearScreen();
                    cout << flush;
                    myKeyboard.disableRawMode();
                    myTerm.gotoxy(0,0);
                    if(setEmployee(&e[*current])){
                        (*current)++;
                        cout<<"YOU NOW HAVE "<<*current<<" EMPLOYEES"<<endl;

                    }
                     myTerm.terminalSleep(1);
                    myKeyboard.enableRawMode();

                    break;
                case KEY_BACKSPACE_CODE:
                case KEY_ESC_CODE:
                    myTerm.clearScreen();
                    cout << flush;
                    return;
        }
        myTerm.clearScreen();
        cout << flush;
        myTerm.displayText(BLUE_COLOR,"Current Employee   "+ to_string(*current),0,0);
        myTerm.displayText(BLUE_COLOR,"Press Enter to create a new employee",0,4);
        myTerm.displayText(RED_COLOR,"Press ESC to exit ",0,8);

    }



}
void displayCurrentEmployees(TerminalModifier& myTerm,Keyboard& myKeyboard,Employee e[],int* current){

     myTerm.clearScreen();
     cout << flush;
     myTerm.displayText(BLUE_COLOR,"List of Employees",0,0);
     myTerm.displayText(BLUE_COLOR,"Number of Employees: "+to_string(*current),0,5);
     cout<<endl;
     cout<<endl;
     displayEmployees(e,*current);
     cout << "\nPress ESC or BACKSPACE key to return to menu..."<<endl;
     while(true){
         int key = myKeyboard.readKey();
         switch(key){
            case KEY_BACKSPACE_CODE:
            case KEY_ESC_CODE:
                        myTerm.clearScreen();
                        cout << flush;
                        return;
            default:
                        ;
         }


     }



}
int main(void) {
    TerminalModifier myTerm;
    Keyboard myKeyboard;
    Employee employeeTable[100];
    int currentEmployee=0;
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

                  int key=myKeyboard.readKey() ;                                                 // First button
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
                                        generateEmployee(myTerm,myKeyboard,employeeTable,&currentEmployee);
                                        printMenu(myTerm, buttons[0], buttons[1],buttons[2],startX,startY);

                                    }else if(currentBtn==1) {
                                         insidePage=true;
                                         displayCurrentEmployees(myTerm,myKeyboard,employeeTable,&currentEmployee);



                                    }
                                    else {
                                        exit=true;
                                    }


                        case KEY_BACKSPACE_CODE:
                            if(insidePage){
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
