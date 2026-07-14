#include <bits/stdc++.h>
using namespace std;

constexpr int MAXM = 105;
constexpr int dx[4] = {-1, 0, 0, 1}, dy[4] = {0, -1, 1, 0};

int m, maze[MAXM][MAXM], dist[MAXM][MAXM][2][3];
struct Node {
    int x, y, c; bool mag;
    int g;
    bool operator<(const Node& other) const { return g > other.g; }
};

int solve() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1][1][0][maze[1][1]] = 0;
    priority_queue<Node, vector<Node>> pq;
    pq.push(Node{1, 1, maze[1][1], false, 0});
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int x = cur.x, y = cur.y, c = cur.c;
        bool mag = cur.mag;  int g = cur.g;
        if (x == m && y == m) 
            return g;
        if (g > dist[x][y][mag==true][c]) continue;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || nx > m || ny < 1 || ny > m) continue;
            int ng, nc = maze[nx][ny]; bool nmag = false;
            if (mag) {
                if (maze[nx][ny] == -1) continue;
                ng = g + (maze[nx][ny] == c ? 0 : 1);
            } else {
                if (maze[nx][ny] == -1) { 
                    nmag = true; 
                    nc = c; ng = g + 2;
                } else ng = g + (maze[nx][ny] == c ? 0 : 1);
            }
            if (ng < dist[nx][ny][nmag==true][nc]) {
                dist[nx][ny][nmag==true][nc] = ng;
                pq.push(Node{nx, ny, nc, nmag, ng});
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(maze, 0xff, sizeof(maze));
    int n, x, y, c;
    cin >> m >> n;
    while (n--) {
        cin >> x >> y >> c;
        maze[x][y] = c;
    }
    int ans = solve();
    cout << ans << '\n';
}