#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3005, R = 8005;

int n, p, tra[N], g[N], r;
int head[N], to[R], nxt[R], ecnt = -1;
stack<int> stk;
int dfn[N], low[N], dfncnt = 0, vis[N], scc[N], scc_cnt = 0;

int cost[N], in[N];

inline void add_edge(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt; 
}

void tar(int u) {
    dfn[u] = low[u] = ++dfncnt;
    vis[u] = 1;
    stk.push(u);
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tar(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v] == 1) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        int v;
        ++scc_cnt;
        do {
            v = stk.top(); stk.pop();
            vis[v] = 2;
            scc[v] = scc_cnt;
            cost[scc_cnt] = min(cost[scc_cnt], g[v]);
        } while (v != u);
    }
}

int main() {
    memset(g, 0x3f, sizeof(g));
    memset(head, -1, sizeof(head));
    memset(cost, 0x3f, sizeof(cost));
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    int x, mon;
    for (int i = 0; i < p; ++i) {
        cin >> x >> mon;
        tra[i] = x - 1; g[tra[i]] = mon;
    }
    cin >> r;
    int u, v;
    for (int i = 0; i < r; ++i) {
        cin >> u >> v;
        --u, --v;
        add_edge(u, v);
    }
    for (int i = 0; i < n; ++i) 
        if (!dfn[i] && g[i] != 0x3f3f3f3f) tar(i);
    for (int i = 0; i < n; ++i) {
        if (!dfn[i]) { 
            cout << "NO\n" << i+1 << '\n';
            return 0;
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int j = head[u]; ~j; j = nxt[j]) {
            int v = to[j];
            if (scc[u] != scc[v]) ++in[scc[v]];
        }
    }
    int ans = 0;
    for (int i = 1; i <= scc_cnt; ++i) {
        if (!in[i]) ans += cost[i];
    }
    cout << "YES\n" << ans << '\n';
    return 0;
}