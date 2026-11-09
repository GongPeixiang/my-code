// dif_up和dif_dn是挂在节点上的延迟差分事件
// 在最后的dfs中完成统计，利用桶的思想
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

const int N = 300005;

int n, m, dep[N], up[N][20], w[N];
struct Edge { int to, nxt; } e[N];
int hd[N], ecnt = 0;

inline void add_edge(int u, int v) {
    e[ecnt] = (Edge){v, hd[u]};
    hd[u] = ecnt++;
}

namespace lca {
void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 20; k++) up[u][k] = up[up[u][k-1]][k-1];
    for (int i = hd[u]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int calc(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 19; ~k; k--) if (dep[u]-(1<<k) >= dep[v]) u = up[u][k];
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

vector<pii> dif_up[N], dif_dn[N];
map<int,int> buc[2];
int ans[N];

void dfs(int u) {
    int tmp1 = buc[0][dep[u]+w[u]], tmp2 = buc[1][dep[u]-w[u]];
    for (int i = hd[u]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == up[u][0]) continue;
        dfs(v);
    }
    for (auto& [key, d]: dif_up[u]) buc[0][key] += d;
    for (auto& [key, d]: dif_dn[u]) buc[1][key] += d;
    ans[u] = buc[0][dep[u]+w[u]] - tmp1 + buc[1][dep[u]-w[u]] - tmp2;
}

int main() {
    memset(hd, -1, sizeof(hd));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    lca::dfs(1, 0);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 1; i <= m; i++) {
        int s, t;
        scanf("%d%d", &s, &t);
        int l = lca::calc(s, t);
        int gf = up[l][0];
        dif_up[s].push_back({dep[s], +1});
        if (gf) dif_up[gf].push_back({dep[s], -1});
        dif_dn[t].push_back({2*dep[l]-dep[s], +1});
        dif_dn[l].push_back({2*dep[l]-dep[s], -1});
    }
    dfs(1);
    for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i==n]);
    return 0;
}