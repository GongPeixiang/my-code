#include <stdio.h>

#define MAXN 350
#define MAXC 40

int N, val[MAXN], cnt[5];
int dp[MAXC + 1][MAXC + 1][MAXC + 1][MAXC + 1];

static inline int max(int a, int b) { return a > b ? a : b; }

int solve() 
{
    dp[0][0][0][0] = val[0];
    for (int a = 0; a <= cnt[1]; ++a) {
        for (int b = 0; b <= cnt[2]; ++b) {
            for (int c = 0; c <= cnt[3]; ++c) {
                for (int d = 0; d <= cnt[4]; ++d) {
                    int r = a + b*2 + c*3 + d*4;
                    if (a >= 1) 
                        dp[a][b][c][d] = max(dp[a][b][c][d], dp[a - 1][b][c][d] + val[r]);
                    if (b >= 1) 
                        dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b - 1][c][d] + val[r]);
                    if (c >= 1) 
                        dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c - 1][d] + val[r]);
                    if (d >= 1) 
                        dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c][d - 1] + val[r]);
                }
            }
        }
    }
    return dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]];
}

int main() 
{
    int M, tmp;
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++i) 
        scanf("%d", &val[i]);
    for (int i = 0; i < M; ++i) {
        scanf("%d", &tmp);
        ++cnt[tmp];
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}
