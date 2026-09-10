#include <bits/stdc++.h>
using namespace std;

const int M = 15, N = 225;
const int MOD = 10007;

int n, m, obit[N], zbit[N], dp[N+1][1<<M];
char maze[N][N];
vector<int> s;

int solve() {
    dp[0][0] = 1;
    for (int r = 1; r <= n; r++) {
        for (int stat: s) {
            for (int nstat: s) {
                if ((nstat&obit[r-1]) != obit[r-1]) continue; // 0-based idx
                if ((~nstat&zbit[r-1]) != zbit[r-1]) continue;
                if ((nstat&stat) == 0) dp[r][nstat] = (dp[r][nstat] + dp[r-1][stat]) % MOD;
            }
        }
    }
    int ans = 0;
    for (int stat: s) ans = (ans + dp[n][stat]) % MOD;
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", maze[i]);
    // always let the matrix to be "thin" n >= m
    if (n < m) {
        char cpy[N][N];
        memcpy(cpy, maze, sizeof(maze));
        swap(n, m);
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < m; j++) 
                maze[i][j] = cpy[j][n-1-i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == '0') zbit[i] += 1<<(m-1-j);
            if (maze[i][j] == '1') obit[i] += 1<<(m-1-j);
        }
    }
    for (int stat = 0; stat < (1<<m); stat++) 
        if ((((stat<<1)|(stat>>1)) & stat) == 0) s.push_back(stat);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}