// 拓扑和floyd都行
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005, M = 10005;

int n, m, in[N];
bool f[N][N];
struct Edge { int to, nxt; } e[M];
int head[N], ecnt = 0;

inline void add_edge(int u, int v) {
    e[ecnt] = (Edge){v, head[u]};
    head[u] = ecnt++;
}

void topo() {
    queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            for (int j = 0; j < n; j++) if (f[j][u]) f[j][v] = 1;
            if (--in[v] == 0) q.push(v);
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        x--; y--;
        add_edge(x, y);
        f[x][y] = 1;
        in[y]++;
    }
    topo();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            if (!f[i][j] && !f[j][i]) ans++;
        }
    }
    printf("%d\n", ans/2);
    return 0;
}