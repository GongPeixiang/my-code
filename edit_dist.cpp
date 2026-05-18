#include <bits/stdc++.h>

constexpr int MAXLEN = 500;

std::string a, b;
int dp[MAXLEN + 5][MAXLEN + 5];

int solve() {
    int n = a.size(), m = b.size();
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i <= n; ++i) 
        dp[i][0] = i;
    for (int i = 0; i <= m; ++i) 
        dp[0][i] = i;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) 
                dp[i][j] = dp[i - 1][j - 1];
            else 
                dp[i][j] = 1 + std::min(dp[i - 1][j - 1], 
                    std::min(dp[i - 1][j], dp[i][j - 1]));
        }
    }
    return dp[n][m];
}

int main() {
    std::cin >> a >> b;
    int ans = solve();
    std::cout << ans << '\n';
    return 0;
}