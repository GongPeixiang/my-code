#include <bits/stdc++.h>
using namespace std;

#define max_3(x,y,z) max(max(x,y),z)

const int N = 45;

int n, t[N][3], dp[2][205][205][205], wm = 0;

int solve() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0] = 0;
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i <= wm; i++) {
            for (int j = 0; j <= wm; j++) {
                for (int k = 0; k <= wm; k++) {
                    int& v = dp[u&1][i][j][k];
                    int p = (u-1) & 1;
                    v = dp[p][i][j][k] + t[u][2];
                    if (i >= t[u][0]) v = min(v, dp[p][i-t[u][0]][j][k]);
                    if (j >= t[u][0]) v = min(v, dp[p][i][j-t[u][0]][k]);
                    if (i >= t[u][1] && k >= t[u][1]) v = min(v, dp[p][i-t[u][1]][j][k-t[u][1]]);
                    if (j >= t[u][1] && k >= t[u][1]) v = min(v, dp[p][i][j-t[u][1]][k-t[u][1]]);
                }
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i <= wm; i++) 
        for (int j = 0; j <= wm; j++) 
            for (int k = 0; k <= wm; k++) 
                ans = min(ans, max_3(i,j,k) + dp[n&1][i][j][k]);
    return ans;
}

int main() {
    scanf("%d", &n);
    int a, b, c, d;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        t[i][0] = a; t[i][1] = c;
        t[i][2] = min(b, d);
        wm += max_3(t[i][0], t[i][1], t[i][2]);
    }
    wm = (wm+1)/2;
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}