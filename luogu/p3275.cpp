#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int N = 100005;

int n, m, in[N], dp[N];
struct Edge { int to, w; };
vector<Edge> g[N], ng[N];

stack<int> stk;
bool instk[N];
int scc[N], tot[N], dfn[N], low[N], dcnt = 0, scnt = 0;

void tar(int u) {
    dfn[u] = low[u] = ++dcnt;
    stk.push(u);
    instk[u] = 1;
    for (const Edge& e: g[u]) {
        int v = e.to;
        if (!dfn[v]) {
            tar(v);
            low[u] = min(low[u], low[v]);
        } else if (instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        int v;
        scnt++;
        do {
            v = stk.top(); stk.pop();
            instk[v] = 0;
            scc[v] = scnt;
            tot[scnt]++;
        } while (v != u);
    }
}

ll solve() { // topo
    queue<int> q;
    for (int i = 1; i <= scnt; i++) {
        if (!in[i]) {
            q.push(i);
            dp[i] = 1;
        }
    }
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (Edge& e: ng[cur]) {
            int v = e.to, w = e.w;
            dp[v] = max(dp[v], dp[cur] + w);
            if (--in[v] == 0) q.push(v);
        }
    }
    ll ans = 0;
    for (int i = 1; i <= scnt; i++) ans += ((ll)dp[i] * tot[i]);
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    int mode = 0, a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &mode, &a, &b);
        a--; b--;
        if (mode == 1) {
            g[a].push_back((Edge){b, 0});
            g[b].push_back((Edge){a, 0});
        } else if (mode == 2) g[a].push_back((Edge){b, 1});
        else if (mode == 3) g[b].push_back((Edge){a, 0});
        else if (mode == 4) g[b].push_back((Edge){a, 1});
        else if (mode == 5) g[a].push_back((Edge){b, 0});
    }
    for (int i = 0; i < n; i++) 
        if (!dfn[i]) tar(i);
    for (int u = 0; u < n; u++) {
        for (Edge& e: g[u]) {
            int v = e.to;
            int su = scc[u], sv = scc[v];
            if (su == sv && e.w == 1) {
                printf("-1\n");
                return 0;
            }
            if (su != sv) {
                ng[su].push_back((Edge){sv, e.w});
                in[sv]++;
            }
        }
    }
    ll ans = solve();
    printf("%lld\n", ans);
    return 0;
}