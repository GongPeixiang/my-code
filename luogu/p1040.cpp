#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MAXN = 40;

int n, score[MAXN], root[MAXN][MAXN];
ll dp[MAXN][MAXN];

ll solve() {
    memset(dp, 0xff, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dp[i][i] = score[i];
        dp[i][i-1] = dp[i+1][i] = 1;
        root[i][i] = i;
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            dp[i][j] = dp[i+1][j] + score[i];
            root[i][j] = i;
            for (int k = i + 1; k <= j; ++k) {
                if (dp[i][k-1] * dp[k+1][j] + score[k] > dp[i][j]) {
                    dp[i][j] = dp[i][k-1] * dp[k+1][j] + score[k];
                    root[i][j] = k;
                }
            }
        }
    }
    return dp[1][n];
}

void print(int l, int r) {
    if (l > r) return;
    cout << root[l][r];
    print(l, root[l][r] - 1);
    print(root[l][r] + 1, r);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) 
        cin >> score[i];
    ll ans = solve();
    cout << ans << '\n';
    print(1, n);
    return 0;
}