#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100005, M = 600005, LOG = 18;
const ll NONE = -1;

int n, m, fa[N], dep[N], up[N][LOG];
ll tot;
ll mx1[N][LOG], mx2[N][LOG];
struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge& o) const { return w < o.w; }
} e[M];
bool vis[M];
vector<pair<int,ll>> g[N];

namespace kruskal {
void init() { for (int i = 0; i < n; i++) fa[i] = i; }

int find(int x) { return x == fa[x] ? x : fa[x]=find(fa[x]); }

bool work() {
    sort(e, e+m);
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int fu = find(e[i].u), fv = find(e[i].v);
        if (fu != fv) {
            vis[i] = 1;
            fa[fv] = fu;
            tot += e[i].w;
            g[e[i].u].push_back(make_pair(e[i].v, e[i].w));
            g[e[i].v].push_back(make_pair(e[i].u, e[i].w));
            cnt++;
        }
    }
    return cnt == n-1;
}
}

namespace lca {
void merge(ll a1, ll a2, ll b1, ll b2, ll& r1, ll& r2) {
    r1 = max(a1, b1);
    if (a1 == b1)      r2 = max(a2, b2);
    else if (a1 > b1)  r2 = max(b1, a2);
    else               r2 = max(a1, b2);
}

void dfs(int u, int p, ll w) {
    up[u][0] = p;
    mx1[u][0] = w;
    mx2[u][0] = NONE;
    for (int k = 1; k < LOG; k++) {
        int a = up[u][k-1];
        up[u][k] = up[a][k-1];
        merge(mx1[a][k-1], mx2[a][k-1], mx1[u][k-1], mx2[u][k-1], mx1[u][k], mx2[u][k]);
    }
    int v; ll w2;
    for (auto& pr: g[u]) {
        tie(v, w2) = pr;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u, w2);
    }
}

pair<ll,ll> query(int u, int v) {
    ll r1 = NONE, r2 = NONE, t1, t2;
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LOG-1; ~k; k--) {
        if (dep[u]-(1<<k) >= dep[v]) {
            merge(r1, r2, mx1[u][k], mx2[u][k], t1, t2);
            r1 = t1; 
            r2 = t2;
            u = up[u][k];
        }
    }
    if (u != v) {
        for (int k = LOG-1; ~k; k--) {
            if (up[u][k] != up[v][k]) {
                merge(r1, r2, mx1[u][k], mx2[u][k], t1, t2);
                r1 = t1; r2 = t2;
                merge(r1, r2, mx1[v][k], mx2[v][k], t1, t2);
                r1 = t1; r2 = t2;
                u = up[u][k];
                v = up[v][k];
            }
        }
        merge(r1, r2, mx1[u][0], mx2[u][0], t1, t2);
        r1 = t1; r2 = t2;
        merge(r1, r2, mx1[v][0], mx2[v][0], t1, t2);
        r1 = t1; r2 = t2;
    }
    return make_pair(r1, r2);
}
}

ll solve() {
    ll ans = -1;
    for (int i = 0; i < m; i++) {
        if (vis[i]) continue;
        pair<ll,ll> d = lca::query(e[i].u, e[i].v);
        ll use = (e[i].w > d.first) ? d.first : d.second;
        if (use != NONE) {
            ll tmp = tot + e[i].w - use;
            if (ans == -1 || tmp < ans) ans = tmp;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    kruskal::init();
    int u, v; ll w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lld", &u, &v, &w);
        u--; v--;
        e[i] = (Edge){u, v, w};
    }
    if (!kruskal::work()) {
        printf("the graph is not connected\n");
        return 0;
    }
    lca::dfs(0, 0, NONE);
    printf("%lld\n", solve());
    return 0;
}