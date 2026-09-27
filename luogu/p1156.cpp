#include <bits/stdc++.h>
using namespace std;

constexpr int MAXD = 105, MAXG = 105;

int D, G, dp[MAXG][MAXD]; // dp[i][h]: max life(first i_th trash at h)
struct Garbage {
    int t, f, h;
} g[MAXG];

int solve() {
    memset(dp, 0xcf, sizeof(dp));
    dp[0][0] = 10; // given in the question
    int ans = 10;
    for (int i = 1; i <= G; ++i) {
        int wait = g[i].t - g[i-1].t;
        for (int d = 0; d <= D; ++d) {
            if (dp[i-1][d] >= wait) {
                dp[i][d] = max(dp[i][d], dp[i-1][d] - wait + g[i].f);
                int nh = min(d + g[i].h, D);
                dp[i][nh] = max(dp[i][nh], dp[i-1][d] - wait);
                if (nh >= D) return g[i].t;
            }
        }
        bool live = false;
        for (int d = 0; d <= D; ++d) 
            if (dp[i][d] >= 0) live = true;
        if (!live) return ans;
        for (int d = 0; d <= D; ++d) {
            if (dp[i][d] >= 0) ans = max(ans, dp[i][d] + g[i].t);
        }
    }
    return ans;
}

int main() {
    scanf("%d %d", &D, &G);
    for (int i = 1; i <= G; ++i) scanf("%d %d %d", &g[i].t, &g[i].f, &g[i].h);
    sort(g + 1, g + G + 1, [](const Garbage& a, const Garbage& b) {
        return a.t < b.t;
    });
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}