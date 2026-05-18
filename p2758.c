#include <stdio.h>
#include <string.h>

#define MAXLEN 2000

char a[MAXLEN + 5], b[MAXLEN + 5];
int dp[MAXLEN + 5][MAXLEN + 5];

static inline int min(int a, int b) { return a < b ? a : b; }

int solve() 
{
    int m = strlen(a), n = strlen(b);
    for (int i = 0; i <= m; ++i) 
        dp[i][0] = i;
    for (int j = 0; j <= n; ++j) 
        dp[0][j] = j;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
                continue;
            }
            dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j]));
        }
    }
    return dp[m][n];
}

int main() 
{
    scanf(" %s %s", a, b);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}