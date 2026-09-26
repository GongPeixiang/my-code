// 本质是支配树问题，此题利用DAG的性质可以做的更简单
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 65534;
// 2^16 = 65536

int n, in[N], dad[N], sz[N];
int up[N][17], dep[N];
vector<int> g[N], ng[N];
char buf[N*2];

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 16; k >= 0; k--) 
        if (dep[u]-(1<<k) >= dep[v]) u = up[u][k];
    if (u == v) return u;
    for (int k = 16; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

void topo() {
    memset(dad, -1, sizeof(dad));
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in[i]) {
            dad[i] = 0;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ng[dad[u]].push_back(u);
        up[u][0] = dad[u];
        dep[u] = dep[dad[u]] + 1;
        for (int k = 1; k < 17; k++) up[u][k] = up[up[u][k-1]][k-1];
        for (int v: g[u]) {
            if (dad[v] == -1) dad[v] = u;
            else dad[v] = lca(dad[v], u);
            if (--in[v] == 0) q.push(v);
        }
    }
}

void dfs(int u) {
    sz[u] = 1;
    for (int v: ng[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
}

int main() {
    scanf("%d", &n);
    while (getchar() != '\n');
    for (int i = 1; i <= n; i++) {
        fgets(buf, sizeof(buf), stdin);
        int j = 0;
        char* tok = strtok(buf, " ");
        while (tok) {
            j = atoi(tok);
            if (!j) break;
            in[i]++;
            g[j].push_back(i);
            tok = strtok(nullptr, " ");
        }
    }
    topo();
    dfs(0);
    for (int i = 1; i <= n; i++) printf("%d\n", sz[i]-1);
    return 0;
}