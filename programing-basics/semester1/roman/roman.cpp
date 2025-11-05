#include <iostream>

int main(){
    int n; std::cin >> n;
    char roman[8] = "MDCLXVI";
    for(int i = 6-(static_cast<int>(n>=10)+static_cast<int>(n>=100)+static_cast<int>(n>=1000))*2; i < 7 and n > 0; i+=2){
        int cur = n;
        for(int j = i/2; j < 3; j++, cur/=10){}
        int nm = cur;
        for(int j = i/2; j < 3; j++, nm*=10){}
        n-=nm;
        if(cur == 9){
            std::cout << roman[i] << roman[i-2];
            continue;
        }
        if(cur >= 5){
            std::cout << roman[i-1]; 
            cur-=5;
        }
        if(cur==4){
            std::cout << roman[i] << roman[i-1];
            cur=0;
        }
        while(cur-- != 0){
            std::cout << roman[i];
        }
    }
    return 0;
}
