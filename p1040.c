#include <stdio.h>
#include <string.h>

typedef long long ll;

#define MAXN 35

int n, score[MAXN], root[MAXN][MAXN];
ll dp[MAXN][MAXN];

ll solve() 
{
    memset(dp, 0xff, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        dp[i][i] = score[i];
        dp[i][i - 1] = dp[i + 1][i] = 1;
        root[i][i] = i;
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            dp[i][j] = dp[i + 1][j] + score[i];
            root[i][j] = i;
            for (int k = i + 1; k <= j; ++k) {
                if (dp[i][k - 1] * dp[k + 1][j] + score[k] > dp[i][j]) {
                    dp[i][j] = dp[i][k - 1] * dp[k + 1][j] + score[k];
                    root[i][j] = k;
                }
            }
        }
    }
    return dp[1][n];
}

void print(int l, int r) 
{
    if (l > r) 
        return;
    printf("%d ", root[l][r]);
    print(l, root[l][r] - 1);
    print(root[l][r] + 1, r);
}

int main() 
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) 
        scanf("%d", &score[i]);
    ll ans = solve();
    printf("%lld\n", ans);
    print(1, n);
    return 0;
}