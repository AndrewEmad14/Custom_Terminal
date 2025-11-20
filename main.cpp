#include <iostream>

using namespace std;
void displayOne(int arr[][5],int rows){
     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }


}
void displayTwo(int *arr,int row,int col){
    for(int i=0;i<row*col;i++){
        cout<<*arr<<endl;
    }

}
int main(void) {
    int x[5][5]={0};
   // displayOne(x,5);
    displayTwo(&x[0][0],5,5);
    return 0;
}
