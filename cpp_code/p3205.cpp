#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 19650827;
int n;
vector<int> h;

int solve() {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) 
        dp[i][i] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (h[i] < h[i + 1]) 
                dp[j][i] += dp[j][i + 1];
            if (h[i] < h[j] && len != 2) {
                dp[j][i] += dp[i + 1][j];
                dp[i][j] += dp[j - 1][i];
            }
            if (h[j] > h[j - 1]) 
                dp[i][j] += dp[i][j - 1];
            dp[i][j] %= MOD, dp[j][i] %= MOD;
            // 每次都要取余
        }
    }
    return (dp[0][n - 1] + dp[n - 1][0]) % MOD; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    h.resize(n);
    for (int i = 0; i < n; ++i) 
        cin >> h[i];
    int ans = solve();
    cout << ans << '\n';
}