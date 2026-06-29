#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 15;

int n, m, grid[MAXN][MAXN], max_val = -1;

int turn(int r, int c) {
    grid[r][c] = (grid[r][c] + 1) % 4;
    int sum = 90;
    int nr, nc;
    switch (grid[r][c]) {
        case 0: 
            nr = r - 1, nc = c; 
            break;
        case 1: 
            nr = r, nc = c + 1; 
            break;
        case 2: 
            nr = r + 1, nc = c; 
            break;
        case 3: 
            nr = r, nc = c - 1; 
            break;
    }
    if (nr >= 0 && nr < n && nc >= 0 && nc < n) 
        sum += turn(nr, nc);
    return sum;
}

void dfs(int dep, int sum) {
    if (dep == m) {
        max_val = max(max_val, sum);
        return;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cpy[MAXN][MAXN];
            memcpy(cpy, grid, sizeof(grid));
            dfs(dep + 1, sum + turn(i, j));
            memcpy(grid, cpy, sizeof(grid));
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }
    dfs(0, 0);
    cout << max_val << '\n';
    return 0;
}