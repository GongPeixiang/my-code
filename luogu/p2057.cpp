#include <bits/stdc++.h>
using namespace std;

const int N = 305, M = 200050;
const int INF = 0X3f3f3f3f;

int n, m, s, t, dep[N];
struct Edge {
    int to, nxt, cap;
} edge[M];
int head[N], ecnt = 0, cur[N];

inline void add_edge(int u, int v, int c) {
    edge[ecnt] = (Edge){v, head[u], c};
    head[u] = ecnt++;
    edge[ecnt] = (Edge){u, head[v], c};
    head[v] = ecnt++; 
}

bool bfs() {
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (dep[v] == -1 && edge[i].cap > 0) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
    return ~dep[t];
}

int dfs(int u, int mf) {
    if (u == t || mf == 0) return mf;
    int sum = 0;
    for (int& i = cur[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (dep[v] == dep[u] + 1 && edge[i].cap > 0) {
            int f = dfs(v, min(mf, edge[i].cap));
            edge[i].cap -= f;
            edge[i^1].cap += f;
            sum += f;
            mf -= f;
            if (!mf) break;
        }
    }
    if (!sum) dep[u] = -1;
    return sum;
}

int dinic() {
    int ans = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        ans += dfs(s, INF);
    }
    return ans;
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    s = 0, t = n + 1;
    int p, u, v;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p);
        if (p) {
            add_edge(s, i, 0); add_edge(i, t, 1);
        } else {
            add_edge(s, i, 1); add_edge(i, t, 0);
        }
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v, 1);
        add_edge(v, u, 1);
    }
    int ans = dinic();
    printf("%d\n", ans);
    return 0;
}