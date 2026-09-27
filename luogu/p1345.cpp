#include <bits/stdc++.h>
using namespace std;

const int N = 105, M = 6005, INF = 0X3f3f3f3f;

int n, m, s, t, dep[N*2];
struct Edge {
    int to, nxt, cap;
} edge[M*2];
int head[N*2], ecnt = 0, cur[N*2];

inline void add_edge(int u, int v, int c) {
    edge[ecnt] = (Edge){v, head[u], c};
    head[u] = ecnt++;
    edge[ecnt] = (Edge){u, head[v], 0};
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

int dfs(int u, int push) {
    if (u == t || !push) return push;
    int sum = 0;
    for (int& i = cur[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (dep[v] == dep[u] + 1 && edge[i].cap > 0) {
            int tmp = dfs(v, min(push, edge[i].cap));
            if (!tmp) continue;
            edge[i].cap -= tmp;
            edge[i^1].cap += tmp;
            push -= tmp;
            sum += tmp;
            if (push == 0) break;
        }
    }
    if (sum == 0) dep[u] = -1;
    return sum;
}

int dinic() {
    int maxflow = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        maxflow += dfs(s, INF);
    }
    return maxflow;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> s >> t;
    s--; t--;
    for (int i = 0; i < n; i++) {
        if (i == s || i == t) add_edge(i, i+n, INF);
        else add_edge(i, i+n, 1);
    }
    int c1, c2;
    for (int i = 0; i < m; i++) {
        cin >> c1 >> c2;
        c1--; c2--;
        add_edge(c1+n, c2, INF);
        add_edge(c2+n, c1, INF);
    }
    t += n;
    int ans = dinic();
    cout << ans << '\n';
    return 0;
}