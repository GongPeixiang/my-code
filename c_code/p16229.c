#include <stdio.h>
#include <string.h>

#define MAXM 5000
#define MAXN 5000
typedef long long ll;

struct Tool {
    ll a, b;
} tools[MAXM + 1];

int n, m, x;
ll dp[MAXN + 1], g[MAXN + 1];

static inline get_min(ll a, ll b) { return a < b ? a : b; }

int main()
{
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 0; i < m; ++i) 
        scanf("%lld %lld", &tools[i].a, &tools[i].b);
    memset(dp, 0x3f, sizeof(dp));
    memset(g, 0x3f, sizeof(g));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            ll aj = tools[j].a, bj = tools[j].b;
            g[i] = get_min(g[i], aj * i + bj * i * (i - 1) / 2);
        }
    }
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] = get_min(dp[i], dp[j] + g[i - j] + (j > 0 ? x : 0));
        }
    }
    printf("%lld", dp[n]);
    return 0;
}
