#include <bits/stdc++.h>
using namespace std;

const int N = 20005, M = 100005;

int n, m, cnt = 0;
vector<int> g[N];
int root, dfn[N], low[N], timer = 0;
bool cut[N];

void tar(int u, int fa) {
    dfn[u] = low[u] = ++timer;
    int ch = 0;
    for (int v: g[u]) {
        if (!dfn[v]) {
            ch++;
            tar(v, u);
            low[u] = min(low[u], low[v]);
            if (u != root && low[v] >= dfn[u]) cut[u] = 1;
            else if (u == root && ch >= 2) cut[u] = 1;
        } else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
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
        if (!dfn[i]) {
            root = i;
            tar(i, 0);
        }
    }
    for (int i = 1; i <= n; i++) if (cut[i]) cnt++;
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++) if (cut[i]) printf("%d ", i);
    putchar('\n');
    return 0;
}