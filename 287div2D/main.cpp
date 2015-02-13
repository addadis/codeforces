#include <iostream>
#include <cstring>
using namespace std;

long long dp[1005][505][2], n, mod, k, pow1[1005], pow2[1005];


int solve(int digit, long long remainder, int flag) {
    if (!digit) {
        return flag;
    }
    if (dp[digit][remainder][flag] != -1) {
        return dp[digit][remainder][flag];
    }
    if (flag) {
        return  ((9 * pow2[digit - 1]) % mod);
    }
    long long temp = 0;

    for (int i = digit == 1? 1 : 0; i < 10; i++) {
        long long newRemainder = (remainder + (long long)i * pow1[n - digit]) % k;
        temp = (temp + solve(digit - 1, newRemainder, flag || (!newRemainder && i))) % mod;
    }
    return dp[digit][remainder][flag] = temp;
}

int main()
{
    cin >> n >> k >> mod;
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow1[i] = (pow1[i-1] * 10) % k;
        pow2[i] = (pow2[i-1] * 10) % mod;
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(n, 0, 0) << endl;
    return 0;
}

