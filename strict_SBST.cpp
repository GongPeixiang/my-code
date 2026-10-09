#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

const int N = 100005, M = 300005;

int n, m, fa[N], dep[N], up[N][18];
struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge& o) const { return w < o.w; }
} e[M];
bool vis[M];
ll tot = 0, mx1[N][18], mx2[N][18];
vector<pair<int,ll>> g[N];

namespace kruskal {
void init() { for (int i = 0; i < n; i++) fa[i] = i; }

int find(int x) { return x == fa[x] ? x : fa[x]=find(fa[x]); }

bool work() {
    using namespace kruskal;
    sort(e, e+m);
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int fu = find(e[i].u), fv = find(e[i].v);
        if (fu != fv) {
            fa[fv] = fu;
            vis[i] = 1;
            tot += e[i].w;
            cnt++;
            g[e[i].u].push_back(make_pair(e[i].v, e[i].w));
            g[e[i].v].push_back(make_pair(e[i].u, e[i].w));
        }
    }
    return cnt == n-1;
}
}

namespace lca {
inline pll merge(pll& a, pll& b) {
    int r1, r2;
    r1 = max(a.first, b.first);
    if (a.first == b.first) r2 = max(a.second, b.second);
    else if (a.first > b.first) r2 = max(a.second, b.first);
    else r2 = max(a.first, b.second);
    return make_pair(r1, r2);
}

void dfs(int u, int p, int d) {
    up[u][0] = p;
    mx1[u][0] = d;
    mx2[u][0] = -1;
    for (int k = 1; k < 18; k++) {
        int a = up[u][k-1];
        up[u][k] = up[a][k-1];
        pll tmp1 = make_pair(mx1[u][k-1],mx2[u][k-1]);
        pll tmp2 = make_pair(mx1[a][k-1], mx2[a][k-1]);
        tie(mx1[u][k], mx2[u][k]) = merge(tmp1, tmp2);
    }
    int v; ll w;
    for (auto& pr: g[u]) {
        tie(v, w) = pr;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u, w);
    }
}

pll query(int u, int v) {
    pll res = make_pair(-1,-1);
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 17; ~k; k--) {
        if (dep[u]-(1<<k) >= dep[v]) {
            pll tmp = make_pair(mx1[u][k], mx2[u][k]);
            res = merge(res, tmp);
            u = up[u][k];
        }
    }
    if (u == v) return res;
    for (int k = 17; ~k; k--) {
        if (up[u][k] != up[v][k]) {
            pll tmp = make_pair(mx1[u][k], mx2[u][k]);
            res = merge(res, tmp);
            tmp = make_pair(mx1[v][k], mx2[v][k]);
            res = merge(res, tmp);
            u = up[u][k];
            v = up[v][k];
        }
    }
    pll tmp = make_pair(mx1[u][0], mx2[u][0]);
    res = merge(res, tmp);
    tmp = make_pair(mx1[v][0], mx2[v][0]);
    res = merge(res, tmp);
    return res;
}
}

ll solve() {
    ll ans = LLONG_MAX;
    for (int i = 0; i < m; i++) {
        if (vis[i]) continue;
        pll pr = lca::query(e[i].u, e[i].v);
        ll d = (e[i].w > pr.first) ? pr.first : pr.second;
        if (~d) ans = min(ans, tot + e[i].w - d);
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    kruskal::init();
    int u, v;  ll w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lld", &u, &v, &w);
        u--; v--;
        e[i] = (Edge){u, v, w};
    }
    bool flg = kruskal::work();
    if (!flg) {
        printf("not connected\n");
        return 0;
    }
    lca::dfs(0, 0, 0);
    ll ans = solve();
    printf("%lld\n", ans);
    return 0;
}