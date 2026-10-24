#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;

int n, in[N], out[N];
bool con[N][N];
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
            vis[v] = 0;
        } while (v != u);
    }
}
}

int main() {
    scanf("%d", &n);
    for (int i = 1, j = 0; i <= n; i++) 
        while (scanf("%d",&j) && j) g[i].push_back(j);
    for (int i = 1; i <= n; i++) if (!tar::dfn[i]) tar::dfs(i);
    if (tar::scnt == 1) { 
        printf("1\n0\n"); 
        return 0; 
    }
    for (int u = 1; u <= n; u++) {
        int uid = tar::scc[u];
        for (int v: g[u]) {
            int vid = tar::scc[v];
            if (vid^uid && !con[uid][vid]) {
                ng[uid].push_back(vid);
                con[uid][vid] = 1;
                in[vid]++;
                out[uid]++;
            }
        }
    }
    int p = 0, q = 0;
    for (int i = 1; i <= tar::scnt; i++) {
        if (!in[i]) p++;
        if (!out[i]) q++;
    }
    printf("%d\n%d\n", p, max(p,q));
    return 0;
}