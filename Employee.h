#include <iostream>
#include <regex>
typedef struct date{
    int year;
    int month;
    int day;


}date;
typedef struct Employee{

        char firstName[20];

        char lastName[20];

        date bod;

}Employee;


bool containsInvalidNameChars(char s[]);
bool isValidDate(int day,int month,int year);
bool setEmployee(Employee *newEmployee);
bool displayEmployees(Employee e[] ,int sizeEmployee );
bool is_leap_year(int year);
bool is_month_long(int month);
