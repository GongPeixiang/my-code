#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int N = 100005, M = 600005;

int n, m, tot = 0, fa[N], dep[N], up[N][18], dis[N][18];
struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const { return w < o.w; }
} e[M];
bool vis[M];
vector<pii> g[N];

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
            vis[i] = 1;
            fa[fv] = fu;
            tot += e[i].w;
            g[fu].push_back(make_pair(fv, e[i].w));
            g[fv].push_back(make_pair(fu, e[i].w));
            cnt++;
        }
    }
    return cnt == n-1;
}
}

namespace lca {
void dfs(int u, int p, int d) {
    up[u][0] = p;
    dis[u][0] = d;
    for (int k = 1; k < 18; k++) {
        up[u][k] = up[up[u][k-1]][k-1];
        dis[u][k] = max(dis[up[u][k-1]][k-1], dis[u][k-1]);
    }
    int v, w;
    for (auto& pr: g[u]) {
        tie(v, w) = pr;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u, w);
    }
}

int query(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int ans = -1;
    for (int k = 17; ~k; k--) {
        if (dep[u]-(1<<k) >= dep[v]) {
            ans = max(ans, dis[u][k]);
            u = up[u][k];
        }
    }
    if (u == v) return ans;
    for (int k = 17; ~k; k--) {
        if (up[u][k] != up[v][k]) {
            ans = max(ans, max(dis[u][k], dis[v][k]));
            u = up[u][k];
            v = up[v][k];
        }
    }
    ans = max(ans, max(dis[u][0], dis[v][0]));
    return ans;
}
}

int solve() {
    int ans = INT_MAX;
    for (int i = 0; i < m; i++) {
        if (vis[i]) continue;
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int d = lca::query(u, v);
        int tmp = tot + w - d;
        ans = min(tmp, ans);
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    kruskal::init();
    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        e[i] = (Edge){u, v, w};
    }
    bool flg = kruskal::work();
    if (!flg) {
        printf("the graph is not connected\n");
        return 0;
    }
    lca::dfs(0, 0, 0);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}