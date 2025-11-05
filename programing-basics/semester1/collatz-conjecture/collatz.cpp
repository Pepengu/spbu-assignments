#include <iostream>

int main(){
    unsigned long long n; std::cin>>n;
    unsigned long long cnt = 0, m = n;
    while(n>1){
        if(m<n){
            m = n;
        }
        if(n%2){
            n=n*3+1;
        }
        else{
            n/=2;
        }
        cnt+=1;
    }
    std::cout << cnt << " " << m;   
    return 0;
}
