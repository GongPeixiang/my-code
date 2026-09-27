#include <bits/stdc++.h>
using namespace std;

const int M = 105, N = 16, C = 25, INF = 0X3f3f3f3f;

int n, g[M][M], maxc = 0, dp[1<<N][C];
struct Rec {
    int x,y,xx,yy;
    int c;
} rec[N];
vector<int> up[N];

bool check(int stat, int i) {
    for (int j: up[i]) 
        if (!((stat>>j) & 1)) return false;
    return true;
}

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= maxc; i++) dp[0][i] = 1;
    for (int stat = 0; stat < (1<<n); stat++) {
        for (int i = 0; i < n; i++) {
            if ((stat<<i) & 1) continue;
            if (check(stat, i)) {
                for (int c = 1; c <= maxc; c++) {
                    int nstat = stat | (1<<i);
                    if (c == rec[i].c) dp[nstat][c] = min(dp[nstat][c], dp[stat][c]);
                    dp[nstat][rec[i].c] = min(dp[nstat][rec[i].c], dp[stat][c] + 1);
                }
            }
        }
    }
    int ans = INF;
    for (int c = 1; c <= maxc; c++) 
        ans = min(ans, dp[(1<<n)-1][c]);
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d%d", &rec[i].x, &rec[i].y, &rec[i].xx, &rec[i].yy,
        &rec[i].c);
        maxc = max(maxc, rec[i].c);
        for (int j = rec[i].x; j < rec[i].xx; j++) 
            for (int k = rec[i].y; k < rec[i].yy; k++) 
                g[j][k] = i;
    }
    for (int i = 0; i < n; i++) {
        up[i].clear();
        if (rec[i].x == 0) continue;
        int ux = rec[i].x - 1;
        int pid = -1; // previous id
        for (int j = rec[i].y; j < rec[i].yy; j++) {
            if (g[ux][j] != pid) {
                up[i].push_back(g[ux][j]);
                pid = g[ux][j];
            }
        }
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}