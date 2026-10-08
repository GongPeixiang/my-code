#include <bits/stdc++.h>
using namespace std;

constexpr int N = 50005, K = 100005;

int n, k, dep[N], up[N][17], dif[N], w[N], ans = 0;
vector<int> g[N];

namespace lca {
void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 17; k++) up[u][k] = up[up[u][k-1]][k-1];
    for (int v: g[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int calc(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 16; ~k; k--) 
        if (dep[u]-(1<<k) >= dep[v]) u = up[u][k];
    if (u == v) return u;
    for (int k = 16; ~k; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}
}

void dfs(int u, int p) {
    w[u] = dif[u];
    for (int v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
        w[u] += w[v];
    }
    ans = max(ans, w[u]);
}

int main() {
    scanf("%d%d", &n, &k);
    int u, v;
    for (int i = 0; i < n-1; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    lca::dfs(1, 0);
    for (int i = 0; i < k; i++) {
        scanf("%d%d", &u, &v);
        dif[u] += 1;
        dif[v] += 1;
        int c = lca::calc(u, v);
        dif[c] -= 1;
        if (up[c][0]) dif[up[c][0]] -= 1;
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}