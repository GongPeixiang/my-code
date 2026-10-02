#include <bits/stdc++.h>
using namespace std;

constexpr int N = 500005;

int n, root, dep[N], up[N][20];
vector<int> g[N];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 20; k++) up[u][k] = up[up[u][k-1]][k-1];
    for (int v: g[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    } 
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 19; k >= 0; k--) 
        if (dep[u]-(1<<k) >= dep[v]) u = up[u][k];
    if (u == v) return u;
    for (int k = 19; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int main() {
    int m;
    scanf("%d%d%d", &n, &m, &root);
    int u, v;
    for (int i = 1; i <= n-1; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(root, root);
    while (m--) {
        scanf("%d%d", &u, &v);
        int f = lca(u, v);
        printf("%d\n", f);
    }
    return 0;
}