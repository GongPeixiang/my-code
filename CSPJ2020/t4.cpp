#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MAXN = 1005;

ll n, m, board[MAXN][MAXN], dp[MAXN][MAXN][3];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> board[i][j];
        }
    }
    memset(dp, 0xcf, sizeof(dp));
    dp[1][1][0] = dp[1][1][1] = dp[1][1][2] = board[1][1];
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n; ++i) 
            dp[i][j][0] = max(dp[i][j-1][0], max(dp[i][j-1][1], dp[i][j-1][2])) + board[i][j];
        for (int i = 2; i <= n; ++i) 
            dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j][0]) + board[i][j];
        for (int i = n - 1; i >= 1; --i) 
            dp[i][j][2] = max(dp[i+1][j][2], dp[i+1][j][0]) + board[i][j];
    }
    ll ans = max(dp[n][m][0], max(dp[n][m][1], dp[n][m][2]));
    cout << ans << '\n';
    return 0;
}