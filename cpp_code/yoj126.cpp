#include <bits/stdc++.h>
using namespace std;

const int MIN = numeric_limits<int>::min();
const array<array<int, 2>, 3> dir = {{ {0, -1}, {1, 0}, {0, 1} }};

int n, m;
vector<vector<int>> matrix;
vector<vector<bool>> visited;

void dfs(int row, int col, int &max_profit, int sum) {
    if (row == n - 1 && col == m - 1) {
        max_profit = max(max_profit, sum);
    }
    for (int i = 0; i < 3; i++) {
        int _row = row + dir[i][0];
        int _col = col + dir[i][1];
        if (_row >= 0 && _row < n && _col >= 0 && _col < m && !visited[_row][_col]) {
            visited[_row][_col] = true;
            dfs(_row, _col, max_profit, sum + matrix[_row][_col]);
            visited[_row][_col] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    matrix.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    visited.resize(n, vector<bool>(m, false));
    int max_profit = MIN;
    visited[0][0] = true;
    dfs(0, 0, max_profit, matrix[0][0]);
    cout << max_profit << '\n';
    return 0;
}