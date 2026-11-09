// 点双连通分量
// 一个点可能在多个点双中
#include <bits/stdc++.h>
using namespace std;

const int N = 500005, M = 4000005;

int n, m, root;
struct Edge { int to, nxt; } e[M];
int hd[N], ecnt = 0;

inline void add_edge(int u, int v) {
    e[ecnt] = (Edge){v, hd[u]};
    hd[u] = ecnt++;
}

namespace tar {
int dfn[N], low[N], timer = 0, dcnt = 0;
stack<int> stk;
vector<int> dcc[N];

void dfs(int u) {
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    if (u == root && hd[u] == -1) {
        dcc[++dcnt].push_back(u);
        return;
    }
    for (int i = hd[u]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                dcnt++;
                int vv;
                do { vv = stk.top(); stk.pop(); dcc[dcnt].push_back(vv); } while (vv != v);
                dcc[dcnt].push_back(u);
            }
        } else low[u] = min(low[u], dfn[v]);
    }
}
}

int main() {
    memset(hd, -1, sizeof(hd));
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        if (u != v) {
            add_edge(u, v);
            add_edge(v, u);
        }
    }
    // 图不一定连通
    for (int i = 1; i <= n; i++) {
        if (!tar::dfn[i]) {
            root = i;
            tar::dfs(i);
        }
    }
    printf("%d\n", tar::dcnt);
    for (int i = 1; i <= tar::dcnt; i++) {
        int sz = tar::dcc[i].size();
        printf("%d ", sz);
        for (int j = 0; j < sz; j++) printf("%d%c", tar::dcc[i][j], " \n"[j==sz-1]);
    }
    return 0;
}