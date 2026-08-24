#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 205;

int n, m, s, t, pre[N];
ll cap[N][N];
bool vis[N];

bool bfs() {
    memset(vis, 0, sizeof(vis));
    vis[s] = true;
    pre[s] = -1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++) {
            if (!vis[v] && cap[u][v] > 0) {
                vis[v] = true;
                pre[v] = u;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

ll max_flow() {
    ll flow = 0;
    while (bfs()) {
        ll d = LLONG_MAX;
        for (int v = t; v != s; v = pre[v]) {
            int u = pre[v];
            d = min(d, cap[u][v]);
        }
        for (int v = t; v != s; v = pre[v]) {
            int u = pre[v];
            cap[u][v] -= d;
            cap[v][u] += d;
        }
        flow += d;
    }
    return flow;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(cap, 0, sizeof(cap));
    cin >> n >> m >> s >> t;
    s--; t--;
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        u--; v--;
        cap[u][v] += w;
    }
    cout << max_flow() << '\n';
    return 0;
}