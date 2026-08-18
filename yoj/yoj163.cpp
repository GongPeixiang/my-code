#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
constexpr int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int n, m, cnt = 0, ans = 0;
char grid[N][N];
bool vis[N][N];

// floodfill
int bfs(int sr, int sc) {
    queue<pair<int,int>> q;
    q.push(make_pair(sr, sc));
    vis[sr][sc] = true;
    int area = 1;
    while (!q.empty()) {
        int r = q.front().first, c = q.front().second; 
        q.pop();
        for (int i = 0; i < 8; i++) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (grid[nr][nc] == '.' || vis[nr][nc]) continue;
            vis[nr][nc] = true;
            q.push(make_pair(nr, nc));
            area++;
        }
    }
    return area;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            cin >> grid[i][j];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'I' && !vis[i][j]) {
                cnt++;
                int area = bfs(i, j);
                ans = max(ans, area);
            }
        }
    }
    cout << cnt << ' ' << ans << '\n';
    return 0;
}