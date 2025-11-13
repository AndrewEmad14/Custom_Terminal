#include <iostream>
#include "TerminalModifier.h"
using namespace std;

int main(void)
{
    TerminalModifier myTerminal;
    myTerminal.gotoxy(10,20);
    cout<<RED_COLOR<<"hi"<<RESET_COLOR<<endl;
    cout<<BOLD<<"hello"<<RESET_COLOR<<endl;
    myTerminal.terminalSleep(3);
    cout<<CLEAR_SCREEN;


    return 0;
}
