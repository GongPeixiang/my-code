#include <bits/stdc++.h>
using namespace std;

const int N = 20005, M = 100005;

int n, m, cnt = 0, root = 0; // 图不一定连通
vector<int> g[N];

namespace tar {
// 无需stack和vis数组标记
int dfn[N], low[N], timer = 0;
bool flg[N]; // cut-vertex

void dfs(int u) {
    dfn[u] = low[u] = ++timer;
    int ch = 0;
    for (int v: g[u]) {
        if (!dfn[v]) {
            ch++;
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (u != root && low[v] >= dfn[u]) flg[u] = 1;
        } else low[u] = min(low[u], dfn[v]);
    }
    if (u == root && ch >= 2) flg[u] = 1;
}
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!tar::dfn[i]) {
            root = i;
            tar::dfs(i);
        }
    }
    for (int i = 1; i <= n; i++) if (tar::flg[i]) cnt++;
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++) if (tar::flg[i]) printf("%d ", i);
    putchar('\n');
    return 0;
}