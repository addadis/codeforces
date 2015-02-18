//problem reduction #1: making a "1" out of n numbers requires their gcd to be 1
//problem reduction #2: for a number x < 10 ^ 9, it has at most 9 prime factors
//solution : subset dp

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <cstring>
#include <string.h>
using namespace std;
int n, jumpLength[500], cost[500], dp[500][1000], mask[500];

void getPrimeFactors(vector<int> & vec, int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            vec.push_back(i);
            while(x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        vec.push_back(x);
    }
}

//calculate the masks of other jump lengths
void calculateMask(vector<int> & vec) {
    int numFactor = vec.size();
    for (int i = 0; i < n; i++) {
        mask[i] = 0;
        for (int j = 0; j < numFactor; j++) {
            if (jumpLength[i] % vec[j] != 0) {
                mask[i] |= (1 << j);
            }
        }
    }
}


int Dp(int currentCard, int Mask, int numFactor) {
    if (currentCard == n + 1) {
        return Mask == (1 << numFactor) - 1 ? 0 : 100000000;
    }

    if (dp[currentCard][Mask] != -1) {
        return dp[currentCard][Mask];
    }

    int & res = dp[currentCard][Mask];
    res = 100000000;
    //we dont choose the current card;
    res = min(res, Dp(currentCard + 1, Mask, numFactor));
    //we choose the current card
    res = min(res, Dp(currentCard + 1, (Mask | mask[currentCard]), numFactor) + cost[currentCard]);
    return res;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> jumpLength[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }

    int ans = 100000000;

    //in each iteration of the loop, we calculate the minimum cost if we buy the ith card
    //the answer is the minimum of one of those
    for (int i = 0; i < n; i++) {
        int x = jumpLength[i];

        //the primeFactors of jumpLength[i]
        vector<int> primeFactors;

        getPrimeFactors(primeFactors, x);

        calculateMask(primeFactors);

        memset(dp, 0xff, sizeof dp);
        //here we add the cost of ith card because inside the Dp it was not added
        ans = min(ans, cost[i] + Dp(1, 0, primeFactors.size()));

    }

    if (ans == 100000000) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}

