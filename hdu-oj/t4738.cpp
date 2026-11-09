// 可处理重边
#include <bits/stdc++.h>
using namespace std;

const int N = 1005, M = 1000005;

int n, m;
struct Edge { int to, w, id; };
vector<Edge> g[N];
vector<int> cut; // 记录割边的权重

namespace tar {
int dfn[N], low[N], _time = 0;

inline void init() { 
    _time = 0; 
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
}

void dfs(int u, int pid) {
    dfn[u] = low[u] = ++_time;
    for (Edge& e: g[u]) {
        int v = e.to, w = e.w, nid = e.id;
        if (nid == (pid^1)) continue;
        if (!dfn[v]) {
            dfs(v, nid);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) cut.push_back(w);
        } else low[u] = min(low[u], dfn[v]);
    }
}
}

int solve() {
    using namespace tar;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            cnt++;
            dfs(i, -1);
        }
    }
    if (cnt > 1) return 0;
    if (cut.empty()) return -1;
    int ans = INT_MAX;
    for (int w: cut) ans = min(ans, max(1, w));
    return ans;
}

int main() {
    while (1) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) break;
        for (int i = 1; i <= n; i++) g[i].clear();
        cut.clear();
        tar::init();
        int u, v, w;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            g[u].push_back((Edge){v, w, 2*i}); // 0-idx
            g[v].push_back((Edge){u, w, 2*i+1});
        }
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}