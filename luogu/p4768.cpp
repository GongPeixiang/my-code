/* NOI2018 T1 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,ll> pil;

#define INF 0x3f3f3f3f3f3f3f3f

constexpr int N = 400005, M = 400005;

int n, m, tot, fa[N], pa[N], up[N][19];
ll dis[N], val[N], mn[N], md[N][19];
struct Edge { 
    int u, v;
    ll w, h;
    bool operator<(const Edge& other) const { return h > other.h; }
} e[M];
vector<pil> g[N]; // 原图仅用于dijkstra
map<int, vector<int>> tr; // 重构树必须单独新建一个图

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

auto cmp = [](pil& a, pil& b){ return a.second > b.second; };

void dij() {
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    priority_queue<pil, vector<pil>, decltype(cmp)> pq(cmp);
    pq.push(make_pair(1,0));
    while (!pq.empty()) {
        pil ud = pq.top(); pq.pop();
        int u = ud.first;
        ll d = ud.second;
        if (d > dis[u]) continue;
        for (pil& vw: g[u]) {
            int v = vw.first;
            ll w = vw.second;
            ll nd = d + w;
            if (nd < dis[v]) {
                dis[v] = nd;
                pq.push(make_pair(v, nd));
            }
        }
    }
}

void kruskal() {
    tot = n;
    for (int i = 1; i <= n; i++) val[i] = INF;
    for (int i = 0; i < m; i++) {
        int u = e[i].u, v = e[i].v;
        ll h = e[i].h;
        int fu = find(u), fv = find(v);
        if (fu == fv) continue;
        val[++tot] = h;
        fa[tot] = fa[fu] = fa[fv] = tot;
        pa[fu] = pa[fv] = tot;
        tr[tot].push_back(fu);
        tr[tot].push_back(fv);
    }
}

/*
void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 19; k++) up[u][k] = up[up[u][k-1]][k-1];
    mn[u] = dis[u];
    if (tr[u].empty()) return;
    for (int v: tr[u]) {
        if (v == p) continue;
        dfs(v, u);
        mn[u] = min(mn[u], mn[v]);
    }
}
*/

// kruskal重构树可以不用dfs构建
void build() {
    for (int i = 1; i <= n; i++) mn[i] = dis[i];
    for (int i = n+1; i <= tot; i++) mn[i] = INF;
    for (int i = n+1; i <= tot; i++) 
        for (int v: tr[i]) mn[i] = min(mn[i], mn[v]);
    for (int i = 1; i <= tot; i++) up[i][0] = pa[i];
    for (int k = 1; k < 19; k++) 
        for (int i = 1; i <= tot; i++) up[i][k] = up[up[i][k-1]][k-1];
}

ll query(int u, int H) {
    for (int k = 18; k >= 0; k--) {
        int p = up[u][k];
        if (p && val[p] > H) u = p;
    }
    return mn[u];
}

int main() {
    int T, q;
    ll k, s;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            g[i].clear();
        }
        tr.clear();
        for (int i = 0; i < m; i++) {
            scanf("%d%d%lld%lld", &e[i].u, &e[i].v, &e[i].w, &e[i].h);
            // 建原图，用于dijkstra
            g[e[i].u].push_back(make_pair(e[i].v, e[i].w));
            g[e[i].v].push_back(make_pair(e[i].u, e[i].w));
        }
        dij();
        sort(e, e+m);
        kruskal();
        build();
        ll ans = 0;
        ll s0, p0;
        scanf("%d%lld%lld", &q, &k, &s);
        while (q--) {
            scanf("%lld%lld", &s0, &p0);
            ll src = (s0 + k*ans - 1) % n + 1;
            ll p = (p0 + k*ans) % (s+1);
            ans = query(src, p);
            printf("%lld\n", ans);
        }
    }
    return 0;
}