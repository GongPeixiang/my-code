#include <stdio.h>
#include <string.h>

#define MAXN 3000

int n, a[MAXN];
int dp[MAXN][MAXN];

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int solve() 
{
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
        if (i != n - 1)
            dp[i][i + 1] = a[i] == a[i + 1] ? 0 : 1;
    }
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (a[i] == a[j]) 
                dp[i][j] = dp[i + 1][j - 1];
            else 
                dp[i][j] = MIN(dp[i + 1][j], 
                        MIN(dp[i][j - 1], dp[i + 1][j - 1])) + 1;
        }
    }
    return dp[0][n - 1];
}
    

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
        scanf("%d", &a[i]);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}
