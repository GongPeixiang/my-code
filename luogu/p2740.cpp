#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 205, M = 1005;

int n, m, pre[N];
ll flow[N];
bool vis[N];
struct Edge {
    int to, nxt;
    ll cap;
} edge[M*2];
int head[N], ecnt = 0;

inline void add_edge(int u, int v, ll c) {
    edge[ecnt] = (Edge){v, head[u], c};
    head[u] = ecnt++;
    edge[ecnt] = (Edge){u, head[v], 0};
    head[v] = ecnt++;
}

ll bfs() {
    memset(vis, 0, sizeof(vis));
    pre[0] = -1;
    vis[0] = true;
    flow[0] = LLONG_MAX;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (!vis[v] && edge[i].cap > 0) {
                vis[v] = true;
                pre[v] = i;
                flow[v] = min(flow[u], edge[i].cap);
                if (v == n - 1) return flow[n-1];
                q.push(v); 
            }
        }
    }
    return 0;
}

ll max_flow() {
    ll ans = 0, add = 0;
    while ((add=bfs()) > 0) {
        ans += add;
        int v = n - 1;
        while (v != 0) {
            int eid = pre[v];
            edge[eid].cap -= add;
            edge[eid^1].cap += add;
            v = edge[eid^1].to;
        }
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> m >> n;
    int s, t, c;
    for (int i = 0; i < m; i++) {
        cin >> s >> t >> c;
        s--; t--;
        add_edge(s, t, c);
    }
    cout << max_flow() << '\n';
    return 0;
}