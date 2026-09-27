#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 205, M = 5005;

int n, m, s, t, dep[N];
struct Edge {
    int to, nxt;
    ll cap;
} edge[M*2];
int head[N], ecnt = 0, cur[N];

inline void add_edge(int u, int v, ll c) {
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

ll dfs(int u, ll mf) {
    if (u == t) return mf;
    ll sum = 0;
    for (int i = cur[u]; ~i; i = edge[i].nxt) {
        cur[u] = i;
        int v = edge[i].to;
        if (dep[v] == dep[u] + 1 && edge[i].cap > 0) {
            ll f = dfs(v, min(mf, edge[i].cap));
            edge[i].cap -= f;
            edge[i^1].cap += f;
            mf -= f;
            sum += f;
            if (mf == 0) break;
        }
    }
    if (sum == 0) dep[u] = 0;
    return sum;
}

ll dinic() {
    ll ans = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        ans += dfs(s, LLONG_MAX);
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> s >> t;
    s--; t--;
    int x, y; ll c;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> c;
        x--; y--;
        add_edge(x, y, c);
    }
    cout << dinic() << '\n';
    return 0;
}