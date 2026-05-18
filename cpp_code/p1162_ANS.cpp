#include <bits/stdc++.h>
using namespace std;

const array<array<int,2>,4> = {{ {-1,0},{0,-1},{1,0},{0,1} }};

int n;
vector<vector<short>> matrix;

void bfs_search(vector<vector<bool>> &visited) {
    queue<pair<int,int>> q;
    // 初始化：将所有边界上的0加入队列
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == 0 || i == n-1 || j == 0 || j == n-1) && matrix[i][j] == 0) {
                q.push({i, j});
                visited[i][j] = true;
            }
        }
    }
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k][0];
            int ny = y + dir[k][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && matrix[nx][ny] == 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    cin >> n;
    matrix.resize(n, vector<short>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    bfs_search(visited);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) cout << 1 << ' ';
            else if (visited[i][j]) cout << 0 << ' ';
            else cout << 2 << ' ';
        }
        cout << '\n';
    }
    return 0;
}