#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1005;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

int n, m, k, d, g[N][N], w[N][N], dis[N][N];
struct Node {
    int x, y;
    int d;
};
queue<Node> q;

void bfs() {
    while (q.size()) {
        Node cur = q.front(); q.pop();
        int x = cur.x, y = cur.y, d = cur.d;
        if (d > dis[x][y]) continue;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
            if (g[nx][ny] == 3) continue;
            if (d + 1 < dis[nx][ny]) {
                dis[nx][ny] = d + 1;
                q.push((Node){nx, ny, d+1});
            }
        }
    }
}

int main() {
    memset(dis, 0x3f, sizeof(dis));
    scanf("%d%d%d%d", &n, &m, &k, &d);
    int x, y, c;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        g[x][y] = 1;
        q.push((Node){x, y, 0});
        dis[x][y] = 0;
    }
    for (int i = 0; i < k; i++) {
        scanf("%d%d%d", &x, &y, &c);
        g[x][y] = 2; 
        w[x][y] += c; // 一个地点可能有多个客户
    }
    for (int i = 0; i < d; i++) {
        scanf("%d%d", &x, &y);
        g[x][y] = 3;
    }
    bfs();
    ll ans = 0;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++) 
            if (w[i][j]) ans += (ll)w[i][j] * dis[i][j]; 
    printf("%lld\n", ans);
    return 0;
}