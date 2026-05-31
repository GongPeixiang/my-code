#include <stdio.h>

#define MAXN 9

int n, a[MAXN + 1][MAXN + 1];
int f[MAXN + 1][MAXN + 1][MAXN + 1][MAXN + 1];

static inline int max(int a, int b) { return a > b ? a : b; }

int solve() 
{
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                for (int l = 1; l <= n; ++l) {
                    f[i][j][k][l]= max(f[i - 1][j][k - 1][l], max(f[i - 1][j][k][l - 1], 
                        max(f[i][j - 1][k - 1][l], f[i][j - 1][k][l - 1])));
					f[i][j][k][l] += a[i][j] + a[k][l]; 
                    //如果位置相同，则减去其中一个
					if(i == k && j == l) f[i][j][k][l] -= a[i][j];  
                }
            }
        }
    }
    return f[n][n][n][n];
}

int main() 
{
    scanf("%d", &n);
    int r, c, val;
    while (1) {
        scanf(" %d %d %d", &r, &c, &val);
        if (!r && !c && !val) break;
        a[r][c] = val;
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}