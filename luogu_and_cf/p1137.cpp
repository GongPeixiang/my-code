#include <bits/stdc++.h>
using namespace std;

constexpr int N = 100005, M = 200005;

int n, m, in[N], dp[N];
struct Edge { int to, nxt; } e[M];
int head[N], ecnt = 0;

inline void add_edge(int u, int v) {
    e[ecnt] = (Edge){v, head[u]};
    head[u] = ecnt++;
}

void topo() {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!in[i]) {
            dp[i] = 1;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            dp[v] = max(dp[v], dp[u] + 1);
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
        in[y]++;
    }
    topo();
    for (int i = 0; i < n; i++) printf("%d\n", dp[i]);
    return 0;
}