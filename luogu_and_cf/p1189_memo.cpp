#include <bits/stdc++.h>
using namespace std;

constexpr int MAXR = 55, MAXN = 1005;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int R, C, n;
char road[MAXR][MAXR];
string dir_seq[MAXN];
bool vis[MAXR][MAXR][MAXN];

void dfs(int r, int c, int dep) {
    if (dep == n) {
        road[r][c] = '*';
        return;
    }
    // 记忆化：如果已经处理过这个状态，直接返回
    if (vis[r][c][dep]) return;
    vis[r][c][dep] = true;

    int idx;
    if (dir_seq[dep] == "NORTH") idx = 0;
    else if (dir_seq[dep] == "SOUTH") idx = 1;
    else if (dir_seq[dep] == "WEST") idx = 2;
    else if (dir_seq[dep] == "EAST") idx = 3;

    int nr = r + dir[idx][0], nc = c + dir[idx][1];
    for (; nr >= 0 && nr < R && nc >= 0 && nc < C; nr += dir[idx][0], nc += dir[idx][1]) {
        if (road[nr][nc] == 'X') break;
        dfs(nr, nc, dep + 1);
    }
}

int main() {
    memset(vis, 0, sizeof(vis));
    int sr, sc;
    cin >> R >> C; 
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> road[i][j];
            if (road[i][j] == '*') {
                sr = i, sc = j;
                road[i][j] = '.';
            }
        }
    }
    cin >> n;
    for (int i = 0; i < n; i++) 
        cin >> dir_seq[i];
    dfs(sr, sc, 0);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) 
            cout << road[i][j];
        cout << '\n';
    }
}