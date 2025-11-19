#include "CustomString.h"
#include <iostream>
#define DEFAULT_VAL 0


                                            //returns char arr size
int str_length(char arr[]){
    int target_size=DEFAULT_VAL;
    while(*(arr)){
        arr++;
        target_size++;

    }
    return target_size;


}

int str_compare(char str1[],char str2[]){
    int sumStr1=DEFAULT_VAL,sumStr2=DEFAULT_VAL;
    int size1=str_length(str1),size2=str_length(str2);
    if(size1<size2)
        return 1;
    else if (size1>size2)
        return -1;
    while(*(str1)||*(str2)){
        if(*(str1)){
            str1++;
            sumStr1+=*str1;
        }
        if(*(str2)){
            str2++;
            sumStr2+=*str2;
        }
    }
    if(sumStr1>sumStr2){
            return -1;

    }else if(sumStr1<sumStr2){
        return 1;
    }else{
        return 0;
    }


}


bool toLower(char str[]){
    int diff='a'-'A';
    while(*(str)){
        if(*str>='A'&&*str<='Z'){
            *str+=diff;
        }
        str++;
    }
    return 1;
}

bool toUpper(char str[]){
    int diff='a'-'A';
    while(*(str)){
        if(*str>='a'&&*str<='z'){
            *str-=diff;
        }
        str++;
    }
    return 1;
}
bool str_concatinate(char str1[],char str2[],int size_str1){
    int str1Length=str_length(str1),str2Length=str_length(str2);
    if(str1Length+str2Length>size_str1)return 0;

    str1+=str1Length;

    while(*(str2)){

        *(str1)=*(str2);

        str1++;
        str2++;
    }
    return 1;
}

bool str_copy(char str1[],char str2[],int size_str2){
    int str1Length=str_length(str1);
    if(str1Length>size_str2)return 0;
    while(*(str1)){
        *(str2)=*(str1);
        str1++;
        str2++;

    }
    return 1;

}
