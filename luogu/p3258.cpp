#include <bits/stdc++.h>
using namespace std;

constexpr int N = 300005;

int n, a[N], dep[N], up[N][20], dif[N], ans[N];
vector<int> g[N];

namespace lca {
void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 20; k++) up[u][k] = up[up[u][k-1]][k-1];
    for (int v: g[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
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

void push_up(int u, int p) {
    ans[u] = dif[u];
    for (int v: g[u]) {
        if (v == p) continue;
        push_up(v, u);
        ans[u] += ans[v];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    int u, v;
    for (int i = 0; i < n-1; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    lca::dfs(1, 0);
    for (int i = 1; i < n; i++) {
        int c = lca::calc(a[i-1], a[i]);
        dif[a[i-1]]++;
        dif[a[i]]++;
        dif[c]--;
        if (up[c][0]) dif[up[c][0]]--;
    }
    push_up(1, 0);
    for (int i = 1; i < n; i++) ans[a[i]]--;
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}