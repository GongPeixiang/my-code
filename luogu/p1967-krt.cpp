#include <bits/stdc++.h>
using namespace std;

constexpr int N = 200005, M = 500005;

int n, m, fa[N], dep[N], up[N][18];
int val[N], cnt;
struct Edge { 
    int u, v, w;
    bool operator<(const Edge& other) const { return w > other.w; }
} e[M];
vector<int> tr[N];

int find(int x) { return x == fa[x] ? x : fa[x]=find(fa[x]); }

void kruskal() {
    sort(e+1, e+m+1);
    for (int i = 1; i <= 2*n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) val[i] = INT_MAX/2;
    cnt = n;
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int fu = find(u), fv = find(v);
        if (fu == fv) continue;
        fa[fu] = fa[fv] = ++cnt;
        val[cnt] = w;
        tr[cnt].push_back(fu);
        tr[cnt].push_back(fv);
        tr[fu].push_back(cnt);
        tr[fv].push_back(cnt);
    }
}

namespace lca {
void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 18; k++) up[u][k] = up[up[u][k-1]][k-1];
    for (int v: tr[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int calc(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 17; ~k; k--) 
        if (dep[u]-(1<<k) >= dep[v]) u = up[u][k];
    if (u == v) return u;
    for (int k = 17; ~k; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    kruskal();
    // memset(dep, -1, sizeof(dep));
    for (int i = 1; i <= cnt; i++) {
        if (fa[i] != i) continue;
        lca::dfs(i, 0);
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &u, &v);
        if (find(u) != find(v)) {
            printf("-1\n");
            continue;
        }
        int c = lca::calc(u, v);
        printf("%d\n", val[c]);
    }
    return 0;
}