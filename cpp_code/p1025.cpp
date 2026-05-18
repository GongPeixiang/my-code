#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200, MAXK = 6;
int n, k;
array<array<int, MAXK + 1>, MAXN + 1> dp = {};

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j == 1 || j == i) 
                dp[i][j] = 1;
            else if (j < i) 
                dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j];
            else if (j > i)
                dp[i][j] = 0;
        }
    }
    cout << dp[n][k] << '\n';
    return 0;
}