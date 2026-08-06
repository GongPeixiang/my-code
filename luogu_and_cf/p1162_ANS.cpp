#include <bits/stdc++.h>
using namespace std;

constexpr int dir[4][3] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
constexpr int MAXN = 35;

int n, mat[MAXN][MAXN];
bool vis[MAXN][MAXN];

void bfs() {
    queue<pair<int,int>> q;
    // 初始化：将所有边界上的0加入队列
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == 0 || i == n-1 || j == 0 || j == n-1) && !mat[i][j]) {
                q.push({i, j});
                vis[i][j] = true;
            }
        }
    }
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !mat[nx][ny] && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    memset(vis, 0, sizeof(vis));
    cin >> n;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            cin >> mat[i][j];    
    bfs();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1) cout << 1 << ' ';
            else if (vis[i][j]) cout << 0 << ' ';
            else cout << 2 << ' ';
        }
        cout << '\n';
    }
    return 0;
}