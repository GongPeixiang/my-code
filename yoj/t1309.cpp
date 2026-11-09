#include <bits/stdc++.h>
using namespace std;

#define sq(x) ((x)*(x))

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
const int N = 55;

int n, m, grid[N][N];
bool vis[N][N];
vector<pair<int,int>> land, money;

void dfs(int r, int c, bool& flg) {
    if (grid[r][c] == 2) {
        money.push_back(make_pair(r, c));
        flg = true;
    }
    land.push_back(make_pair(r, c));
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i], nc = c + dy[i];
        if (nr < 0 && nr >= n && nc < 0 && nc >= m) continue;
        if (!vis[nr][nc] && grid[nr][nc]) {
            vis[nr][nc] = true;
            dfs(nr, nc, flg);
        }
    }
}

int cal() {
    int minc = 0x3f3f3f3f;
    for (auto p : land) {
        int tmp = 0;
        for (auto tp: money) 
            tmp = max((int)(sqrt(sq(p.first-tp.first)+sq(p.second-tp.second))), tmp);
        minc = min(tmp, minc);
    }
    return minc;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            cin >> grid[i][j];
    int cnt = 0, cost = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] && !vis[i][j]) {
                vis[i][j] = true;
                land.clear(); money.clear();
                bool flg = (grid[i][j] == 2);
                dfs(i, j, flg);
                if (flg) {
                    cnt++;
                    cost += cal();
                }
            }
        }
    }
    cout << cnt << ' ' << cost << '\n';
    return 0;
}