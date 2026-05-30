#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 205, MAXK = 10;

int n, k, dp[MAXN][MAXK];

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j == 1 || j == i) 
                dp[i][j] = 1;
            else if (j < i) 
                dp[i][j] = dp[i-1][j-1] + dp[i-j][j];
            else if (j > i)
                dp[i][j] = 0;
        }
    }
    cout << dp[n][k] << '\n';
    return 0;
}