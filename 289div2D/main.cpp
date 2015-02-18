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
int n, m;
long long mat[105][105], a[105], b[105], mod;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        b[i] = mat[0][i];
    }

    for (int i = 1; i < n; i++) {
        a[i] = mat[i][0] - b[0];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] + b[j] != mat[i][j]) {
                mod = abs(a[i] + b[j] - mat[i][j]);
            }
        }
    }
    if (!mod) {
        mod = 200000000000000;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (((long long)a[i] + b[j] + mod) % mod != mat[i][j]) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    cout << "YES" << endl << mod << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] + mod << " ";
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << b[i] + mod << " ";
    }
    return 0;
}

