#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105, M = 505;

int n, m, _w[N], _v[N], in[N];
bool con[N][N];
int nw[N], nv[N], dp[N][M];
vector<int> g[N], ng[N];

namespace tar {
int dfn[N], low[N], timer = 0, scc[N], scnt = 0;
stack<int> stk;
bool vis[N];

void dfs(int u) {
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    vis[u] = 1;
    for (int v: g[u]) {
        if (!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int v;
        scnt++;
        do {
            v = stk.top(); stk.pop();
            scc[v] = scnt;
            nw[scnt] += _w[v];
            nv[scnt] += _v[v];
            vis[v] = 0;
        } while (v != u);
    }
}
}

void dfs(int u) {
    memset(dp[u], -1, sizeof(dp[u]));
    for (int j = nw[u]; j <= m; j++) dp[u][j] = nv[u];
    for (int v: ng[u]) {
        dfs(v);
        for (int j = m; j >= nw[u]; j--) {
            for (int k = nw[v]; k <= j-nw[u]; k++) {
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k]);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &_w[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &_v[i]);
    int fa;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &fa);
        g[fa].push_back(i);
    }
    for (int i = 1; i <= n; i++) if (!tar::dfn[i]) tar::dfs(i);
    for (int u = 1; u <= n; u++) {
        int uid = tar::scc[u];
        for (int v: g[u]) {
            int vid = tar::scc[v];
            if (vid ^ uid && !con[uid][vid]) {
                ng[uid].push_back(vid);
                con[uid][vid] = 1;
                in[vid]++;
            }
        }
    }
    for (int i = 1; i <= tar::scnt; i++) if (!in[i]) ng[0].push_back(i);
    dfs(0);
    printf("%d\n", dp[0][m]);
    return 0;
}