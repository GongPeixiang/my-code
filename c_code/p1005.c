#include <stdio.h>
#include <string.h>

#define MAXN 80
#define MAXM 80

static inline __int128 max(__int128 a, __int128 b) { return a > b ? a : b; }

void output(__int128 num) 
{
    if (num > 9) 
        output(num / 10);
    putchar(num % 10 + '0');
}

int n, m, matrix[MAXN][MAXM];
__int128 dp[MAXM][MAXN], pow2[MAXM + 5];

void init_tab() 
{
    for (int i = 1; i <= m; ++i) 
        pow2[i] = (__int128)1 << i;
}

__int128 solve(const int r) 
{
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < m; ++i) 
        dp[i][i] = matrix[r][i] * pow2[m];
    for (int len = 2; len <= m; ++len) {
        for (int i = 0; i + len - 1 < m; ++i) {
            int j = i + len - 1;
            dp[i][j] = max(dp[i][j - 1] + matrix[r][j] * pow2[m - len + 1], dp[i + 1][j] + matrix[r][i] * pow2[m - len + 1]);
        }
    }
    return dp[0][m - 1];
}

int main() 
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf(" %d", &matrix[i][j]);
        }
    }
    init_tab();
    __int128 ans = 0;
    for (int i = 0; i < n; ++i) 
        ans += solve(i);
    output(ans);
    printf("\n");
    return 0;
}