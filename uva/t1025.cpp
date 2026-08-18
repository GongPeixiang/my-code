#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 55, MAXT = 205, INF = 0x3f3f3f3f;

int n, T, g[MAXN], m1, m2, dp[MAXT][MAXN]; 
// 状态定义:二元组(i,j)表示时刻i位于第j个车站
// dp[i][j]表示从状态(i,j)到达状态(T,n)所需的最少等待时间. 目标:dp[0][1]
bool ok[2][MAXN][MAXT];

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[T][n] = 0;
    for (int i = T - 1; i >= 0; i--) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i+1][j] + 1;
            if (j < n && ok[0][i][j] && i + g[j] <= T) dp[i][j] = min(dp[i][j], dp[i+g[j]][j+1]);
            if (j > 1 && ok[1][i][j] && i + g[j-1] <= T) dp[i][j] = min(dp[i][j], dp[i+g[j-1]][j-1]);
        }
    }
    return (dp[0][1] >= INF) ? -1 : dp[0][1];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int kase = 0, t = 0;
    while (1) {
        cin >> n;
        if (!n) break;
        ++kase;
        memset(g, 0, sizeof(g));
        memset(ok, 0, sizeof(ok));
        cin >> T;
        for (int i = 1; i < n; i++) cin >> g[i];
        cin >> m1;
        for (int i = 1; i <= m1; i++) {
            cin >> t;
            for (int j = 1; j <= n; j++) {
                ok[0][t][j] = true;
                t += g[j];
            }
        }
        cin >> m2;
        for (int i = 1; i <= m2; i++) {
            cin >> t;
            for (int j = n; j >= 1; j--) {
                ok[1][t][j] = true;
                t += g[j-1];
            }
        }
        cout << "Case number " << kase << ": ";
        int ans = solve();
        if (~ans) cout << ans << '\n';
        else cout << "impossible\n";
    }
    return 0;
}