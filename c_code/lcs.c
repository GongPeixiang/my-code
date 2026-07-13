#include <stdio.h>
#include <string.h>

#define MAXLEN 105

char a[MAXLEN], b[MAXLEN];
int dp[MAXLEN][MAXLEN];

static inline int get_max(int a, int b) { return a > b ? a : b; }

int solve() 
{
    int n = strlen(a), m = strlen(b);
    for (int i = 0; i <= n; ++i) dp[i][0] = 0;
    for (int i = 0; i <= m; ++i) dp[0][i] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i-1] == b[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
            else dp[i][j] = get_max(dp[i][j-1], dp[i-1][j]);
        }
    }
    return dp[n][m];
}

int main() 
{
    scanf("%s %s", a, b);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}