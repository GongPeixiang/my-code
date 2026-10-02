/* 
最大瓶颈路问题，生成树+LCA
也可以用kruskal重构树实现。
kruskal重构树使用范围更广，不仅可以处理瓶颈路问题，还能处理【从x出发只走权值≥T 的边，能到哪些点】这类问题
*/
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

#define INF 0x3f3f3f3f
constexpr int N = 10005, M = 50005;

int n, m, fa[N], dep[N], up[N][16], dist[N][16];
struct Edge{ 
    int u, v, w; 
    bool operator<(const Edge& other) const { return w > other.w; }
} e[M];
vector<pii> g[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int x, int y) { fa[find(x)] = find(y); }

void kruskal() {
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 0; i < m; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (find(u) == find(v)) continue;
        merge(u, v);
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }
}

void dfs(int u, int p, int d) {
    up[u][0] = p;
    dist[u][0] = d;
    for (int k = 1; k < 16; k++) {
        up[u][k] = up[up[u][k-1]][k-1];
        dist[u][k] = min(dist[u][k-1], dist[up[u][k-1]][k-1]);
    }
    for (auto& vw: g[u]) {
        int v = vw.first, w = vw.second;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u, w);
    }
}

int lca(int u, int v) {
    if (find(u)^find(v)) return -1;
    if (dep[u] < dep[v]) swap(u, v);
    int ans = INF;
    for (int k = 15; k >= 0; k--) {
        if (dep[u]-(1<<k) >= dep[v]) {
            ans = min(ans, dist[u][k]);
            u = up[u][k];
        }
    }
    if (u == v) return ans;
    for (int k = 15; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            ans = min(ans, min(dist[u][k], dist[v][k]));
            u = up[u][k];
            v = up[v][k];
        }
    }
    ans = min(ans, min(dist[u][0], dist[v][0]));
    return ans;
}

int main() {
    memset(dep, -1, sizeof(dep));
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 0; i < m; i++) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    sort(e, e+m);
    kruskal();
    memset(dep, -1, sizeof(dep));
    for (int i = 1; i <= n; i++) {
        if (~dep[i]) continue;
        dep[i] = 0;
        dfs(i, i, INF);
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &u, &v);
        int ans = lca(u, v);
        printf("%d\n", ans);
    }
    return 0;
}