#include <bits/stdc++.h>
using namespace std;

constexpr int N = 10005;

int n, m, out[N];
vector<int> g[N];

namespace tar {
int dfn[N], low[N], timer = 0, tot[N], scc[N], scnt = 0;
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
            tot[scnt]++;
            vis[v] = 0;
        } while (v != u);
    }
}
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) if (!tar::dfn[i]) tar::dfs(i);
    for (int u = 1; u <= n; u++) {
        int uid = tar::scc[u];
        for (int v: g[u]) if (tar::scc[v] != tar::scc[u]) out[uid]++;
    }
    vector<int> ans;
    for (int i = 1; i <= tar::scnt; i++) 
        if (out[i] == 0) ans.push_back(tar::tot[i]);
    if (ans.size() > 1) printf("0\n");
    else printf("%d\n", ans[0]);
    return 0;
}