#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

constexpr int N = 300005, M = 300005;

int n, m, dep[N], up[N][20], dis[N], fa[M], dif[N]; // 每条边的lca只算一次，存下来
vector<pii> g[N];
pii e[M];

namespace lca {
void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 20; k++) up[u][k] = up[up[u][k-1]][k-1];
    int v, t;
    for (auto& pr: g[u]) {
        tie(v, t) = pr;
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dis[v] = dis[u] + t;
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

void dfs(int u, int p) {
    int v, t;
    for (auto& pr: g[u]) {
        tie(v, t) = pr;
        if (v == p) continue;
        dfs(v, u);
        dif[u] += dif[v];
    }
}

bool check(int T) {
    memset(dif, 0, sizeof(dif));
    int cnt = 0, maxd = -1;
    int u, v;
    for (int i = 0; i < m; i++) {
        tie(u, v) = e[i];
        int c = fa[i];
        int d = dis[u] + dis[v] - 2 * dis[c];
        if (d > T) {
            dif[u]++; dif[v]++;
            dif[c] -= 2;
            cnt++;
        }
        maxd = max(maxd, d);
    }
    if (cnt == 0) return true;
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        if (dif[i] == cnt) {
            if (maxd - (dis[i]-dis[up[i][0]]) <= T) return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v, t;
    int l = INT_MAX, r = 0;
    for (int i = 1; i <= n-1; i++) {
        scanf("%d%d%d", &u, &v, &t);
        g[u].push_back(make_pair(v, t));
        g[v].push_back(make_pair(u, t));
        l = min(l, t);
    }
    lca::dfs(1, 0);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        e[i] = make_pair(u, v);
        fa[i] = lca::calc(u, v);
        int d = dis[u] + dis[v] - 2 * dis[fa[i]];
        r = max(r, d);
    }
    while (l < r) {
        int mid = l + ((r-l)>>1);
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}