#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MAXN = 1005, MAXH = 20005;
constexpr ll MOD = 998244353ll;

int n, h[MAXN], maxh = -1;
ll dp[MAXN][2 * MAXH];
// dp[i][dh] 表示以第i个元素结尾,公差为(dh - maxh),长度≥2的等差数列的个数

int main() {
    memset(dp, 0, sizeof(dp));
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
        maxh = max(h[i], maxh);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int dh = maxh + h[i] - h[j];
            dp[i][dh] = (dp[i][dh] + dp[j][dh] + 1) % MOD;
        }
    }
    ll ans = n;
    for (int i = 0; i < n; ++i) {
        for (int dh = 0; dh <= 2 * maxh; ++dh) {
            ans = (ans + dp[i][dh]) % MOD;
        }
    }
    cout << ans << '\n';
    return 0;
}