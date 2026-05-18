#include <stdio.h>
#include <string.h>

#define MAXN 50

int n;
char str[MAXN + 5];
int dp[MAXN][MAXN];

static inline int min(int a, int b) { return a < b ? a : b; }

int solve() 
{
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; ++i) 
        dp[i][i] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (str[i] == str[j]) 
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]);
            else {
                for (int k = i; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                } 
            }
        }
    }
    return dp[0][n - 1];
}

int main()
{
    scanf("%s", str);
    n = strlen(str);
    int ans = solve();
    printf("%d\n", ans);
}