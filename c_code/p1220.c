#include <stdio.h>
#include <string.h>

#define MAXN 50

int n, c, sum[MAXN];
struct Light {
    int s, w;
} a[MAXN];
int dp[MAXN][MAXN][2];

static inline int get_min(int a, int b) { return a < b ? a : b; }

int solve() 
{
    memset(dp, 0x3f, sizeof(dp));
    dp[c][c][0] = dp[c][c][1] = 0;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            int t1 = a[j].s - a[i].s, t2 = a[i + 1].s - a[i].s;
            int t3 = a[j].s - a[i].s, t4 = a[j].s - a[j - 1].s;
            int d1 = t1 * (sum[i] + sum[n - 1] - sum[j]);
            int d2 = t2 * (sum[i] + sum[n - 1] - sum[j]);
            int d3 = t3 * ((i ? sum[i - 1] : 0) + sum[n - 1] - sum[j - 1]);
            int d4 = t4 * ((i ? sum[i - 1] : 0) + sum[n - 1] - sum[j - 1]);
            dp[i][j][0] = get_min(dp[i][j][0],
                get_min(dp[i + 1][j][1] + d1, dp[i + 1][j][0] + d2));
            dp[i][j][1] = get_min(dp[i][j][1],
                get_min(dp[i][j - 1][0] + d3, dp[i][j - 1][1] + d4));
        }
    }
    return get_min(dp[0][n - 1][0], dp[0][n - 1][1]);
}

int main() 
{
    scanf("%d %d", &n, &c);
    --c;
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &a[i].s, &a[i].w);
        if (!i) 
            sum[i] = a[i].w;
        else 
            sum[i] = sum[i - 1] + a[i].w;
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}