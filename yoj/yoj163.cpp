#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 8> dir = {{ {-1, 1}, {-1, 0}, {-1, -1}, 
    {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1} }};

int n, m;
vector<vector<char>> board;

void dfs(vector<vector<bool>> &visited, int row, int col, 
    int& area) {
    area++;
    for (int i = 0; i < 8; ++i) {
        int nr = row + dir[i][0];
        int nc = col + dir[i][1];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && 
            !visited[nr][nc] && board[nr][nc] == 'I') {
                visited[nr][nc] = true;
                dfs(visited, nr, nc, area);
            }
    }
}

int main() {
    cin >> n >> m;
    board.resize(n, vector<char>(m));    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
        }
    }
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int cnt = 0;
    int max_area = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == 'I' && !visited[i][j]) {
                visited[i][j] = true;
                int area = 0;
                dfs(visited, i, j, area);
                max_area = max(max_area, area);
                ++cnt;
            }
        }
    }
    cout << cnt << ' ' << max_area << '\n';
    return 0;
}