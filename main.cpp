#include <iostream>
#include "CustomString.h"

using namespace std;


int main(void) {
    char a[10]="ANdREw";
    char b[10]="";
    cout<<str_copy(a,b,10)<<endl;
    printf("%s",b);


    return 0;
}
