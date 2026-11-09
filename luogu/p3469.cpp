#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

int n, m, root = 1;
vector<int> g[N];
ll ans[N];

namespace tar {
int dfn[N], low[N], sz[N], timer = 0;

void dfs(int u) {
    dfn[u] = low[u] = ++timer;
    sz[u] = 1;
    ll sum = 0, sq = 0, ch = 0;
    bool cut = 0;
    for (int v: g[u]) {
        if (!dfn[v]) {
            ch++;
            dfs(v);
            sz[u] += sz[v];
            low[u] = min(low[u], low[v]);
            if (u != root && low[v] >= dfn[u]) cut = 1;
            if (low[v] >= dfn[u]) {
                // low[v] >= dfn[u] 说明u作为割点时v的子树会与其他部分不连通
                sum += (ll)sz[v];
                sq += (ll)sz[v] * sz[v];
            }
        } else low[u] = min(low[u], dfn[v]);
    }
    if (u == root && ch > 1) cut = 1;
    if (cut) ans[u] = 2*(n-1) + 2*(n-1-sum)*sum + (sum*sum - sq);
    else ans[u] = 2*(n-1);
}
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        // 题目保证无重边
        g[u].push_back(v);
        g[v].push_back(u);
    }
    tar::dfs(root);
    for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
    return 0;
}