#include <bits/stdc++.h>
using namespace std;

const int N = 5005, M = 20005;

int n, m, in[N];
struct Edge { int from, to, nxt; } e[M];
int hd[N], ecnt = 0;

inline void add_edge(int u, int v) {
    e[ecnt] = (Edge){u, v, hd[u]};
    hd[u] = ecnt++;
}

int dfn[N], low[N], _time = 0;
int dcc[N], dcnt = 0;
bool bridge[N];

void tar(int u, int pid) {
    dfn[u] = low[u] = ++_time;
    for (int i = hd[u]; ~i; i = e[i].nxt) {
        if (i == (pid^1)) continue;
        int v = e[i].to;
        if (!dfn[v]) {
            tar(v, i);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) bridge[i] = bridge[i^1] = 1;
        } else low[u] = min(low[u], dfn[v]);
    }
}

void dfs(int u) {
    dcc[u] = dcnt;
    for (int i = hd[u]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dcc[v] && !bridge[i]) dfs(v);
    }
}

int main() {
    memset(hd, -1, sizeof(hd));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) tar(i, -1);
    for (int i = 1; i <= n; i++) {
        if (!dcc[i]) {
            dcnt++;
            dfs(i);
        }
    }
    for (int i = 0; i < m; i++) { // 不能逐点遍历，因为无向图已经加了双向边
        int u = e[2*i].from, v = e[2*i].to;
        if (dcc[u] != dcc[v]) {
            in[dcc[u]]++;
            in[dcc[v]]++;
        }
    }
    int lf = 0;
    for (int i = 1; i <= dcnt; i++) if (in[i] == 1) lf++;
    int ans = (lf+1)/2;
    printf("%d\n", ans);
    return 0;
}