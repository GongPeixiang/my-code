#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define MAXM 10000

int n, m;
struct Mouse {
    int t;
    int x, y;
} mouse[MAXM];
int dp[MAXM];

static inline int max(int a, int b) { return a > b ? a : b; }

static inline int dist(int x, int y, int xx, int yy) { return abs(x - xx) + abs(y - yy); }

int solve() 
{
    for (int i = 0; i < m; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (dist(mouse[i].x, mouse[i].y, mouse[j].x, mouse[j].y) 
                <= mouse[i].t - mouse[j].t) 
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    int ans = -1;
    for (int i = 0; i < m; ++i) 
        ans = max(ans, dp[i]);
    return ans;
}

int main() 
{
    scanf(" %d %d", &n, &m);
    for (int i = 0; i < m; ++i) 
        scanf(" %d %d %d", &mouse[i].t, &mouse[i].x, &mouse[i].y);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}