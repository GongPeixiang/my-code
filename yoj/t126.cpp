#include <bits/stdc++.h>
using namespace std;

constexpr int dir[3][2] = {{0, -1}, {1, 0}, {0, 1}};
constexpr int MAXN = 10, MAXM = 10;

int n, m, board[MAXN][MAXM], max_val = 0xcfcfcfcf;
bool vis[MAXN][MAXM];

void dfs(int r, int c, int sum) {
    if (r == n - 1 && c == m - 1) {
        max_val = max(max_val, sum);
        return;
    }
    for (int i = 0; i < 3; ++i) {
        int nr = r + dir[i][0], nc = c + dir[i][1];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m) 
            continue;
        if (!vis[nr][nc]) {
            vis[nr][nc] = true;
            dfs(nr, nc, sum + board[nr][nc]);
            vis[nr][nc] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
        }
    }
    vis[0][0] = true; // 标记起点
    dfs(0, 0, board[0][0]);
    cout << max_val << '\n';
    return 0;
}