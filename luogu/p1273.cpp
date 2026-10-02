#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3005;

int n, m, sz[N], dp[N][N]; // m <= n-1
struct Edge {
    int to, nxt, w;
} e[N];
int head[N], ecnt = 0;

inline void add_edge(int u, int v, int w) {
    e[ecnt] = (Edge){v, head[u], w};
    head[u] = ecnt++;
}

void dfs(int u) {
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w;
        dfs(v);
        sz[u] += sz[v];
        if (sz[u] > m) sz[u] = m;
        for (int j = min(sz[u], m); j > 0; j--) 
            for (int k = 0; k <= j && k <= sz[v]; k++) 
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k] - w);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    memset(dp, 0xcf, sizeof(dp));
    scanf("%d%d", &n, &m);
    int k, v, c;
    for (int i = 1; i <= n-m; i++) {
        scanf("%d", &k);
        while (k--) {
            scanf("%d%d", &v, &c);
            add_edge(i, v, c);
        }
    }
    for (int i = n-m+1; i <= n; i++) {
        scanf("%d", &dp[i][1]);
        sz[i] = 1;
    }
    for (int i = 1; i <= n; i++) dp[i][0] = 0;
    dfs(1);
    for (int i = m; i >= 0; i--) {
        if (dp[1][i] >= 0) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}