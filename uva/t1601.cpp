#include <bits/stdc++.h>
using namespace std;

const int M = 20, S = 200; // 16*16*0.75 = 192
const int dx[5] = {-1, 0, 1, 0, 0}, dy[5] = {0, -1, 0, 1, 0};

int g[S][5], src[3], dst[3], dist[S][S][S];
char maze[M][M];
struct Node {
    int a, b, c;
} pre[S][S][S];

inline bool illegal(int x, int y, int nx, int ny) {
    return x == y || (x == ny && y == nx);
}

int solve() {
    memset(dist, 0x3f, sizeof(dist));
    dist[src[0]][src[1]][src[2]] = 0;
    queue<Node> q;
    q.push((Node){src[0], src[1], src[2]});
    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        int a = cur.a, b = cur.b, c = cur.c;
        if (a == dst[0] && b == dst[1] && c == dst[2]) return dist[a][b][c];
        for (int i = 0; i < 5; i++) {
            if (g[a][i] == -1) continue;
            int na = g[a][i];
            for (int j = 0; j < 5; j++) {
                if (g[b][j] == -1) continue;
                int nb = g[b][j];
                if (illegal(a,b,na,nb)) continue;
                for (int k = 0; k < 5; k++) {
                    if (g[c][k] == -1) continue;
                    int nc = g[c][k];
                    if (illegal(a,c,na,nc) || illegal(b,c,nb,nc)) continue;
                    int nd = dist[a][b][c] + 1;
                    if (nd < dist[na][nb][nc]) {
                        dist[na][nb][nc] = nd;
                        q.push((Node){na, nb, nc});
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    int w, h, n, x[S], y[S], id[M][M];
    while (1) {
        scanf("%d%d%d", &w, &h, &n);
        if (w == 0) break;
        while (getchar() != '\n');
        memset(g, -1, sizeof(g));
        memset(id, -1, sizeof(id));
        for (int i = 0; i < h; i++) {
            fgets(maze[i], sizeof(maze[i]), stdin);
            maze[i][strcspn(maze[i], "\r\n")] = '\0';
        }
        int cnt = 0;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (maze[i][j] == '#') continue;
                x[cnt] = i; y[cnt] = j;
                id[i][j] = cnt;
                if (islower(maze[i][j])) src[maze[i][j]-'a'] = cnt;
                if (isupper(maze[i][j])) dst[maze[i][j]-'A'] = cnt;
                cnt++;
            }
        }
        for (int i = 0; i < cnt; i++) {
            for (int d = 0; d < 5; d++) {
                int nx = x[i] + dx[d], ny = y[i] + dy[d];
                if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
                if (maze[nx][ny] != '#') g[i][d] = id[nx][ny];
            }
        }
        if (n <= 2) {
            src[2] = dst[2] = cnt;
            int (&gs)[5] = g[src[2]];
            gs[0] = cnt++;
            gs[1] = gs[2] = gs[3] = gs[4] = -1;
        }
        if (n <= 1) {
            src[1] = dst[1] = cnt;
            int (&gs)[5] = g[src[1]];
            gs[0] = cnt++;
            gs[1] = gs[2] = gs[3] = gs[4] = -1;
        }
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}