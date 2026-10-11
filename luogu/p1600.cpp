/*
 * 树上差分可以分2个阶段分别累加
 * 先不考虑【桶】的使用：
 * tg_up[s]++; tg_up[fa[lca]]--;
 * tg_dn[t]++; tg_dn[lca]--;
 * 分 dfs_up 和 dfs_dn
 * 
 * 这个题需要额外用桶的思想处理
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 300005;

int n, m, w[N], dep[N], up[N][20], ans[N];
vector<pair<int,int>> tg1[N], tg2[N];
vector<int> g[N];
map<int,int> buc;

namespace lca {
void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 20; k++) up[u][k] = up[up[u][k-1]][k-1];
    for (int v: g[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int calc(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 19; ~k; k--) 
        if (dep[u]-(1<<k) >= dep[v]) u = up[u][k];
    if (u == v) return u;
    for (int k = 19; ~k; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}
}

void dfs_up(int u) {
    int cur = buc[dep[u]+w[u]];
    for (int v: g[u]) if (v != up[u][0]) dfs_up(v);
    for (auto& p: tg1[u]) buc[p.first] += p.second;
    ans[u] += (buc[dep[u]+w[u]] - cur);
}

void dfs_dn(int u) {
    int cur = buc[dep[u]-w[u]];
    for (int v: g[u]) if (v != up[u][0]) dfs_dn(v);
    for (auto& p: tg2[u]) buc[p.first] += p.second;
    ans[u] += (buc[dep[u]-w[u]] - cur);
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= n-1; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    lca::dfs(1, 0);
    int s, t;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &s, &t);
        int c = lca::calc(s, t);
        tg1[s].push_back(make_pair(dep[s], 1));
        if (up[c][0]) tg1[up[c][0]].push_back(make_pair(dep[s], -1));
        tg2[t].push_back(make_pair(2*dep[c]-dep[s], 1));
        tg2[c].push_back(make_pair(2*dep[c]-dep[s], -1));
    }
    dfs_up(1);
    buc.clear();
    dfs_dn(1);
    for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i==n]);
    return 0;
}