#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};
int n;
vector<vector<int>> grid;

void dfs(vector<vector<bool>> &visited, int row, int col) {
    if (!visited[row][col] && grid[row][col] == 0) {
        visited[row][col] = true;
        for (int d = 0; d < 4; d++) {
            int _r = row + dir[d][0], _c = col + dir[d][1];
            if (_r >= 0 && _r < n && _c >= 0 && _c < n) {
                dfs(visited, _r, _c);
            }
        }
    }
}

int main() {
    cin >> n;
    grid.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) 
        dfs(visited, i, 0);
    for (int j = 0; j < n; j++) 
        dfs(visited, 0, j);
    for (int i = 0; i < n; i++) 
        dfs(visited, i, n - 1);
    for (int j = 0; j < n; j++) 
        dfs(visited, n - 1, j);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && !visited[i][j]) 
                cout << 2 << ' ';
            else 
                cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}