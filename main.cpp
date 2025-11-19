#include <iostream>

using namespace std;
void swapUsingPlus(int *x,int *y){

    *x=*x+*y;
    *y=*x-*y;
    *x=*x-*y;
}
void swapUsingMultiply(int *x,int *y){

        *x=(*x)*(*y);
        *y=(*x)/ (*y);
        *x=(*x)/ (*y);

}
void swapUsingXOR(int *x,int *y){
        *x=(*x)^(*y);
        *y=(*x)^(*y);
        *x=(*x)^(*y);
}

int main(void) {
    int x=10,y=5;
    swapUsingPlus(&x,&y);
    swapUsingXOR(&x,&y);
    swapUsingXOR(&x,&y);
    cout<<"X: "<<x<<" Y: "<<y<<endl;
    return 0;
}
