#include <bits/stdc++.h>
using namespace std;

constexpr int N = 200005;

int n;
vector<int> g[N];

namespace tar {
int dfn[N], low[N], timer = 0, scc[N], scnt = 0, tot[N];
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
            vis[v] = 0;
            tot[scnt]++;
        } while (v != u);
    }
}
}

int main() {
    scanf("%d", &n);
    int fa;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &fa);
        g[fa].push_back(i);
    }
    for (int i = 1; i <= n; i++) if (!tar::dfn[i]) tar::dfs(i);
    int ans = INT_MAX;
    for (int i = 1; i <= tar::scnt; i++) {
        if (tar::tot[i] == 1) continue;
        ans = min(ans, tar::tot[i]);
    }
    printf("%d\n", ans);
    return 0;
}