#include "Employee.h"
#include <iostream>
using namespace std;
bool setEmployee(Employee* newEmployee){


    cout << "\nEmployee Information:\n";
    cout<<"First name: ";
    cin>>newEmployee->firstName;
    if(containsInvalidNameChars(newEmployee->firstName)){
        cout<<"Please enter a valid first name"<<endl;
        return false;
    }
    cout<<endl;
    cout<<"Last name: ";
    cin>>newEmployee->lastName;
     if(containsInvalidNameChars(newEmployee->lastName)){
        cout<<"Please enter a valid last name"<<endl;
        return false;
    }
    cout<<"Date:"<<endl;
    cout<<"Day: ";
    cin>>newEmployee->bod.day;
    cout<<endl;
    if(newEmployee->bod.day)
    cout<<"Month: ";
    cin>>newEmployee->bod.month;
    cout<<endl;
    cout<<"Year: ";
    cin>>newEmployee->bod.year;
    cout<<endl;
    if(isValidDate(newEmployee->bod.day,newEmployee->bod.month,newEmployee->bod.year)){
            cout<<"Enter a valid Date"<<endl;
        return false;
    }
    return true;
}

bool displayEmployees(Employee e[] ,int sizeEmployee ){

    for(int i=0;i<sizeEmployee;i++){
        cout << "Employee Number:\n";
        cout << "Name: " << e[i].firstName << " " << e[i].lastName << endl;
        cout << "Date of Birth: " << e[i].bod.day << "/" << e[i].bod.month << "/" << e[i].bod.year << endl;
        cout<<"========================================================================"<<endl;

    }
    return true;

}
bool containsInvalidNameChars(char s[]){
    return regex_search(s,regex("[^A-Za-z]"));
}
bool isValidDate(int day,int month,int year){
    if(!is_month_long(month)){
            if(month == 2){ // February
                if(is_leap_year(year)){
                    if(day > 29){
                        cout<<"Invalid day for February in a leap year. Please try again."<<endl;
                        return false;
                    }
                } else {
                    if(day > 28){
                        cout<<"Invalid day for February. Please try again."<<endl;
                        return false;
                    }
                }
            } else if(day > 30){
                cout<<"Invalid day for the given month. Please try again."<<endl;
                        return false;
            }
        } else {
            if(day > 31){
                cout<<"Invalid day for the given month. Please try again."<<endl;
                        return false;
            }
        }
        return true;
}
bool is_month_long(int month){
    int long_months[] = {0, 2, 4, 6, 7, 9, 11};
    return find(begin(long_months), end(long_months), month) != end(long_months);
}
bool is_leap_year(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
