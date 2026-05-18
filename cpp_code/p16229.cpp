#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Tool {
    ll a, b;
};

int n, m, x;
vector<Tool> tools;

ll solve() {
    vector<ll> dp(n + 1, 1e18), g(n + 1, 1e18);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            ll aj = tools[j].a, bj = tools[j].b;
            g[i] = min(g[i], aj * i + bj * i * (i - 1) / 2);
        }
    }
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] = min(dp[i], dp[j] + g[i - j] + (j > 0 ? x : 0));
        }
    }
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> x;
    tools.resize(m);
    for (int i = 0; i < m; ++i) 
        cin >> tools[i].a >> tools[i].b;
    ll ans = solve();
    cout << ans << '\n';
}