#include <bits/stdc++.h>
using namespace std;

constexpr int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
constexpr int MAXN = 55;
constexpr int MAXM = 55;
using Point = pair<int, int>;

int n, m, grid[MAXN][MAXM];
bool vis[MAXN][MAXM];

struct Island {
    vector<Point> land, treasures;
};

void dfs(int r, int c, Island &island, bool &flg) {
    if (grid[r][c] == 2) {
        island.treasures.push_back({r, c});
        flg = true;
    }
    island.land.push_back({r, c});
    for (int i = 0; i < 4; i++) {
        int nr = r + dir[i][0], nc = c + dir[i][1];
        if (nr < 0 && nr >= n && nc < 0 && nc >= m) 
            continue;
        if (!vis[nr][nc] && grid[nr][nc]) {
            vis[nr][nc] = true;
            dfs(nr, nc, island, flg);
        }
    }
}

int cal_cost(const Island &island) {
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
                bool has_treasure = (grid[i][j] == 2);
                dfs(i, j, cur_land, has_treasure);
                if (has_treasure) {
                    ++cnt;
                    cost += cal_cost(cur_land);
                }
            }
        }
    }
    cout << cnt << ' ' << cost << '\n';
    return 0;
}