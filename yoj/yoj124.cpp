#include<bits/stdc++.h>
using namespace std;

constexpr int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
constexpr int MAXR = 55;

int R, C, h[MAXR][MAXR], memo[MAXR][MAXR];

int dfs(int r, int c) {
    if (memo[r][c] != -1) 
        return memo[r][c];
    int max_len = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dir[i][0], nc = c + dir[i][1];
        if (nr >= 0 && nr < r && nc >= 0 && nc < c && h[nr][nc] < h[r][c]) 
            max_len = max(max_len, 1 + dfs(nr, nc));
    }
    memo[r][c] = max_len;
    return max_len;
}

int main() {
    memset(memo, 0xff, sizeof(memo));
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> h[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            ans = max(ans, dfs(i, j));
        }
    }
    cout << ans << '\n';
    return 0;
}