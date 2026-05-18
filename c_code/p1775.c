#include <stdio.h>
#include <string.h>

#define MAXN 300

int N, m[MAXN], sum[MAXN];
int dp[MAXN][MAXN];

static inline int get_min(int a, int b) { return a < b ? a : b; }

int solve()
{
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < N; ++i) 
        dp[i][i] = 0;
    for (int len = 2; len <= N; ++len) {
        for (int i = 0; i + len - 1 < N; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                int add = sum[j] - (i > 0 ? sum[i - 1] : 0);
                dp[i][j] = get_min(dp[i][j], dp[i][k] + dp[k + 1][j] + add);
            }
        }
    }
    return dp[0][N - 1];
}

int main() 
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &m[i]);
        if (!i) 
            sum[i] = m[i];
        else
            sum[i] = m[i] + sum[i - 1];
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}