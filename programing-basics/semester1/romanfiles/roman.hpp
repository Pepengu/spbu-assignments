#ifndef ROMAN_H
#define ROMAN_H

#include <fstream>

void foutRoman(std::ofstream& fout, int n){
    if(n==0){
        fout << 0;
        return;
    }
    char roman[8] = "MDCLXVI";
    int starting_index = 6-(static_cast<int>(n>=10)+static_cast<int>(n>=100)+static_cast<int>(n>=1000))*2;
    for(int i = starting_index; i < 7 && n > 0; i+=2){
        int cur = n;
        for(int j = i/2; j < 3; j++, cur/=10){}
        int nm = cur;
        for(int j = i/2; j < 3; j++, nm*=10){}
        n-=nm;
        if(cur == 9){
            fout << roman[i] << roman[i-2];
            continue;
        }
        if(cur >= 5){
            fout << roman[i-1]; 
            cur-=5;
        }
        if(cur==4){
            fout << roman[i] << roman[i-1];
            cur=0;
        }
        while(cur-- != 0){
            fout << roman[i];
        }
    }
}

#endif
