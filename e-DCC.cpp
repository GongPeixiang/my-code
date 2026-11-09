// 边双连通分量
// 一个点只能在一个边双中
#include <bits/stdc++.h>
using namespace std;

const int N = 500005, M = 4000005;

int n, m;
struct Edge { int to, id; };
vector<Edge> g[N];
int dcc[N], dcnt = 0;
vector<int> buc[N];

namespace tar {
int dfn[N], low[N], _time = 0;
bool bridge[M];

void dfs(int u, int pid) {
    dfn[u] = low[u] = ++_time;
    for (Edge& e: g[u]) {
        int v = e.to, id = e.id;
        if (id == (pid^1)) continue;
        if (!dfn[v]) {
            dfs(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) bridge[id] = bridge[id^1] = 1;
        } else low[u] = min(low[u], dfn[v]);
    }
}
}

void dfs(int u) {
    dcc[u] = dcnt;
    for (Edge& e: g[u]) {
        int v = e.to, id = e.id;
        if (!tar::bridge[id] && !dcc[v]) dfs(v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (u == v) continue; // 自环
        g[u].push_back((Edge){v, 2*i});
        g[v].push_back((Edge){u, 2*i+1});
    }
    for (int i = 1; i <= n; i++) if (!tar::dfn[i]) tar::dfs(i, -1);
    for (int i = 1; i <= n; i++) {
        if (!dcc[i]) {
            ++dcnt;
            dfs(i);
        }
    }
    printf("%d\n", dcnt);
    for (int i = 1; i <= n; i++) buc[dcc[i]].push_back(i);
    for (int i = 1; i <= dcnt; i++) {
        printf("%zu ", buc[i].size());
        for (int u: buc[i]) printf("%d ", u);
        putchar('\n');
    }
    return 0;
}