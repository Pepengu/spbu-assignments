#include <iostream>

void floor_and_room_number(int n){
    unsigned long long l = 0, r = n;
    unsigned long long mid;

    while(l+1 < r){
        mid = (l + r)/2;

        if(mid*(mid+1)*(2*mid+1)/6 < n)
            l = mid;
        else
            r = mid;
    }

    unsigned long long rooms_on_sq = n-l*(l+1)*(2*l+1)/6;

    std::cout << l*(l+1)/2 + rooms_on_sq/(l+1) + (rooms_on_sq%(l+1)!=0) << " " << (rooms_on_sq-1)%(l+1)+1 << "\n";
}

int main(){
    int n; std::cin >> n;
    floor_and_room_number(n);
    return 0;
}
