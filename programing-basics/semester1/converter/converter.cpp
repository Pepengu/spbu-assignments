#include <iostream>

void coutDigit(int n){
    if(n < 10){
        std::cout << n; 
    }
    else{
        std::cout << (char)('A'+n-10);
    }
}

void from10toN(int n, int base){
    if(n < base){
        coutDigit(n);
        return;
    }

    from10toN(n/base, base);
    coutDigit(n%base);
}

int main(){
    int n, base; std::cin >> n >> base;
    from10toN(n, base);
    return 0;
}
