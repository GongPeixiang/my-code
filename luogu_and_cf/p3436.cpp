#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1000005, M = 1000005;

int n, m, in[N], dp[N], tcnt = 0;
bool vis[N], flg[N];
struct Edge { int to, nxt; } e[M];
int head[N], ecnt = 0;

inline void add_edge(int u, int v) {
    e[ecnt] = (Edge){v, head[u]};
    head[u] = ecnt++;
}

void bfs() { // floodfill
    vis[n] = 1;
    queue<int> q;
    q.push(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
} 

void topo() {
    queue<int> q;
    dp[n] = 1;
    flg[n] = 1;
    q.push(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        tcnt++;
        flg[u] = 1;
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (v == n) { // 主楼在环上，特判
                tcnt = 0;
                memset(flg, 0, sizeof(flg));
                return;
            }
            if (!vis[v]) continue;
            dp[v] += dp[u];
            if (dp[v] > 36500) dp[v] = 36501;
            if (--in[v] == 0) q.push(v);
        }
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        x--; y--;
        add_edge(y, x);
    }
    bfs();
    // 排除不可达点
    for (int u = 0; u <= n; u++) {
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (vis[u] && vis[v]) in[v]++;
        }
    }
    topo();
    // 两种可能大于36500，第一种是并非无穷但是确实大于36500，第二种是无穷(反映到拓扑排序就是不在拓扑序列中)
    if (tcnt < n + 1) {
        for (int i = 0; i < n; i++) 
            if (vis[i] && !flg[i]) dp[i] = 36501;
    }
    int maxs = -1;
    vector<int> ans;
    for (int i = 0; i < n; i++) maxs = max(maxs, dp[i]);
    // q1
    if (maxs == 36501) printf("zawsze\n");
    else printf("%d\n", maxs);
    // q2
    for (int i = 0; i < n; i++) 
        if (dp[i] == maxs) ans.push_back(i);
    printf("%d\n", ans.size());
    // q3
    for (int u: ans) printf("%d ", u+1);
    putchar('\n');
    return 0;
}