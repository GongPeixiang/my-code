#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1005;

int n, dp[MAXN][MAXN];
string seq;

int solve() {
    for (int i = 0; i < n; ++i) 
        dp[i][i] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (seq[i] == seq[j]) dp[i][j] = 2 + dp[i+1][j-1];
            else dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
        }
    }
    return dp[0][n-1];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> seq;
    memset(dp, 0, sizeof(dp));
    int ans = solve();
    cout << ans << '\n';
}