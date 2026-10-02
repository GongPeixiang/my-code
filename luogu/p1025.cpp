/*
Q: 如何想到这个思路?
A:
dp[i][j] = ∑ k=1...j dp[i-j][k],这需要3层循环

优化：注意到 dp[i-1][j-1] = ∑ k=1...(j-1) dp[i-1][k] 

于是, dp[i][j] = dp[i-1][j-1] + dp[i-j][j];
*/

#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205, K = 7;

int n, k, dp[N][K];

int solve() {
    for (int i = 1; i <= n; i++) dp[i][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            dp[i][j] = dp[i-1][j-1];
            if (i > j) dp[i][j] += dp[i-j][j];
        }
    }
    return dp[n][k];
}

int main() {
    scanf("%d%d", &n, &k);
    int ans = solve();
    printf("%d\n", ans);
}