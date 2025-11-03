#include <iostream>

bool isLeap(int year){
    return (year%4==0 and year%100!=0) or year%400==0;
}

int main(){
    int day;
    int month;
    int year;
    char dot1;
    char dot2;
    std::cin >> day >> dot1 >> month >> dot2 >> year;
    bool has_to_be_leap = isLeap(year);
    if(dot1 != '.' or dot2 != '.'){
        std::cout << "Unknown";
        return 0;
    }
    if(month == 2){
        if(day < 0 or day > 28 + (has_to_be_leap ? 1 : 0)){
            std::cout << "Unknown";
            return 0;
        }
    }
    else if(day < 1 or day > 30 + (month < 8 ? month%2 : 1-month%2)){
        std::cout << "Unknown";
        return 0;
    }
    if(year < 1 or month < 1 or month > 12){
        std::cout << "Unknown";
        return 0;
    }
    int a = (14-month)/12;
    int y = year-a;
    int m = month +12*a-2;
    int d = (day+y+y/4-y/100+y/400+31*m/12)%7;
    switch(d){
        case 1:
            std::cout << "Monday";
            break;
        case 2:
            std::cout << "Tuesday";
            break;
        case 3:
            std::cout << "Wednesday";
            break;
        case 4:
            std::cout << "Thursday";
            break;
        case 5:
            std::cout << "Friday";
            break;
        case 6:
            std::cout << "Saturday";
            break;
        case 0:
            std::cout << "Sunday";
            break;
    }

    do{
        if(has_to_be_leap){
            year+=4;
            if(!isLeap(year)){
                continue;
            }
        }
        else{
            year++;
        }
        y = year-a;
        d = (day+y+y/4-y/100+y/400+31*m/12)%7;      
    }  while(d!=5);

    std::cout << "\n" << year;
    return 0;
}
