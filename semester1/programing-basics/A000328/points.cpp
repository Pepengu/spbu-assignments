#include <iostream>

void solve(){
    long long r; std::cin>> r;
    long long cnt = 0, y = r;
    for (long long i = 1; i < r; ++i) {
        while (i*i + y*y > r*r)
            --y;
        cnt += y;
    }

    std::cout << 4*cnt + 4*r + 1 << "\n";
}

int main () {
    solve();
    return 0;
}
