#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MAXN = 100005, MAXLEN = 5005;
constexpr int MOD = 1000000007;

int n, a[MAXN];
int len_cnt[MAXLEN], max_l = -1, min_l = 0x3f3f3f3f;

int solve() {
    ll ans = 0;
    for (int i = min_l + 1; i <= max_l; ++i) {
        if (len_cnt[i] < 2) continue;
        ll c1 = (len_cnt[i] * (len_cnt[i] - 1)) / 2;
        for (int j = min_l; j <= i / 2; ++j) {
            if (len_cnt[j] && len_cnt[i - j]) {
                ll c2;
                if (j == i - j) 
                    c2 = (len_cnt[j] * (len_cnt[j] - 1)) / 2;
                else 
                    c2 = len_cnt[j] * len_cnt[i - j];
                ans = (ans + (c1 * c2) % MOD) % MOD;
            }
        }
    }
    return ans % MOD;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ++len_cnt[a[i]];
        max_l = max(a[i], max_l);
        min_l = min(a[i], min_l);
    }
    int ans = solve();
    cout << ans << '\n';
    return 0;
}