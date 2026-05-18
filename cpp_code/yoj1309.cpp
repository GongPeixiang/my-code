#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};
int n, m, INF = 1e9;
vector<vector<int>> grid;

struct Island {
    vector<pair<int, int>> land, treasures;
};

void dfs(int r, int c, vector<vector<bool>> &visited, Island &island, bool &hasTreasure) {
    if (grid[r][c] == 2) {
        island.treasures.push_back({r, c});
        hasTreasure = true;
    }
    island.land.push_back({r, c});
    for (int i = 0; i < 4; i++) {
        int nr = r + dir[i][0], nc = c + dir[i][1];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc] && grid[nr][nc]) {
            visited[nr][nc] = true;
            dfs(nr, nc, visited, island, hasTreasure);
        }
    }
}

int min_energy(const Island &island) {
    int min_energy = INF;
    for (auto p : island.land) {
        int tmp = 0;
        for (auto tp : island.treasures) {
            tmp = max((int)(sqrt(pow(p.first - tp.first, 2) + pow(p.second - tp.second, 2))),tmp);
        }
        min_energy = min(tmp, min_energy);
    }
    return min_energy;
}

int main() {
    cin >> n >> m;
    grid.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int cnt = 0, energy = 0;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] && !visited[i][j]) {
                visited[i][j] = true;
                Island island;
                bool hasTreasure = (grid[i][j] == 2);
                dfs(i, j, visited, island, hasTreasure);
                if (hasTreasure) {
                    cnt++;
                    energy += min_energy(island);
                }
            }
        }
    }
    cout << cnt << ' ' << energy << '\n';
    return 0;
}