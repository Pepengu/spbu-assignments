#include <iostream>

using namespace std;

struct input{
    int n;
    int k;
};


long long partition(input in);

int main () {
	int n = 0;
	int k = 0;
	std::cin >> n >> k;
	std::cout << partition({n, k});
	return 0;
}

long long partition(input in){
    int n = in.n;
    int k = in.k;
    long long *dp = new long long[n+1];
    for(int i = 0; i <= n; ++i){
        dp[i] = 0;
    }
    
    for (int i = 1; i <= k; ++i) {
        long long prev = dp[i];
        dp[i-1] = 0;
        dp[i] = 1;
        for (int j = i+1; j <= n; ++j) {
            long long cur = dp[j];

            dp[j] = prev + dp[j - i];
            prev = cur;
        }
    }


    long long ans = dp[n];
    delete[] dp;
    return ans;
}
		
