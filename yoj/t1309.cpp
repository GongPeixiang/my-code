#include <bits/stdc++.h>
using namespace std;

constexpr int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
constexpr int N = 55;
using Point = pair<int, int>;

int n, m, grid[N][N];
bool vis[N][N];

struct Island {
    vector<Point> land, treasures;
};

void dfs(int r, int c, Island& island, bool& flg) {
    if (grid[r][c] == 2) {
        island.treasures.push_back({r, c});
        flg = true;
    }
    island.land.push_back({r, c});
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i], nc = c + dy[i];
        if (nr < 0 && nr >= n && nc < 0 && nc >= m) continue;
        if (!vis[nr][nc] && grid[nr][nc]) {
            vis[nr][nc] = true;
            dfs(nr, nc, island, flg);
        }
    }
}

int cal_cost(const Island& island) {
    int min_cost = 0x3f3f3f3f;
    for (auto p : island.land) {
        int tmp = 0;
        for (auto tp: island.treasures) 
            tmp = max((int)(sqrt(pow(p.first - tp.first, 2)+pow(p.second - tp.second, 2))), tmp);
        min_cost = min(tmp, min_cost);
    }
    return min_cost;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int cnt = 0, cost = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] && !vis[i][j]) {
                vis[i][j] = true;
                Island cur_land;
                bool flg = (grid[i][j] == 2);
                dfs(i, j, cur_land, flg);
                if (flg) {
                    cnt++;
                    cost += cal_cost(cur_land);
                }
            }
        }
    }
    cout << cnt << ' ' << cost << '\n';
    return 0;
}