#include <stdio.h>

typedef long long ll;

#define MAXN 1005
#define MAXH 20005
#define MOD 998244353ll

int n, max_h = - 1, h[MAXN];
ll dp[MAXN][2 * MAXH];
// +max_h的偏移量

ll solve() 
{
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ++ans;
        for (int j = 0; j < i; ++j) {
            int dh = h[i] - h[j] + max_h;
            dp[i][dh] = (dp[i][dh] + dp[j][dh] + 1) %  MOD;
        }
        for (int k = 0; k <= 2 * max_h; ++k) 
            ans = (ans + dp[i][k]) % MOD;
    }
    return ans % MOD;
}

int main() 
{
    scanf(" %d", &n);
    for (int i = 0; i < n; ++i) {
        scanf(" %d", &h[i]);
        max_h = max_h > h[i] ? max_h : h[i];
    }
    ll ans = solve();
    printf("%lld\n", ans);
    return 0;
}