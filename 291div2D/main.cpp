#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <math.h>
using namespace std;
int droids[100005][6], rmq[6][100005][50], ans[6], temp[6], n, m, k;

void rmqProcess() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            rmq[i][j][0] = droids[j][i];
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int k = 0; k + (1 << j) - 1 < n; k++) {
                rmq[i][k][j] = max(rmq[i][k][j - 1], rmq[i][k + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int getMax(int i, int j, int index) {
    int diff = j - i + 1;
    int power = 0;
    while((1 << power) <= diff) {
        power++;
    }
    power--;
    int ret = max(rmq[index][i][power], rmq[index][j - (int)pow(2, power) + 1][power]);
    temp[index] = ret;
    return ret;
}

void findMaxLength() {
    int maxLength = 0;
    int leftPointer = 0;
    int rightPointer = 0;
    while(true) {
        if (rightPointer >= n) {
            break;
        }
        int sum = 0;
        for (int i = 0; i < m; i++) {
            sum += getMax(leftPointer, rightPointer, i);
        }
        if (sum <= k) {
            if (maxLength < rightPointer - leftPointer + 1) {
                maxLength = rightPointer - leftPointer + 1;
                for (int i = 0; i < m; i++) {
                    ans[i] = temp[i];
                }
            }
            rightPointer++;
        } else {
            leftPointer++;
            while (leftPointer > rightPointer) {
                rightPointer++;
            }
        }

    }
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> droids[i][j];
        }
    }
    rmqProcess();
    findMaxLength();
    for (int i = 0; i < m; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}

