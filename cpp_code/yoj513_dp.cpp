#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int m, n; // 添加 m 个加号,本质上分成 (m+1)段
string line;

ll solve() {
    int n = line.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i && j <= m; ++j) {
            for (int k = j - 1; k < i; ++k) {
                int r = i - 1, l = k;
                ll add = stoll(line.substr(l, r - l + 1));
                dp[i][j] = max(dp[i][j], dp[k][j-1] + add);
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) 
        ans = max(ans, dp[i][m]);
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> line;
    ++m;
    ll ans = solve();
    cout << ans << '\n';
}