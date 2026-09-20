#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5005, M = 100005;

int n, m, in[N], ans[N];
struct Edge { int to, nxt; } e[M];
int head[N], ecnt = 0;

inline void add_edge(int u, int v) {
    e[ecnt] = (Edge){v, head[u]};
    head[u] = ecnt++;
}

bool topo() {
    int cnt = 0;
    queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    bool flg = 0;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        ans[cnt++] = cur;
        int t = 0;
        for (int i = head[cur]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            in[v]--;
            if (in[v] == 0) {
                t++;
                q.push(v);
            }
        }
        if (t > 1) flg = 1;
    }
    return flg;
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        u--; v--;
        add_edge(u, v);
        in[v]++;
    }
    bool f = topo();
    for (int i = 0; i < n; i++) printf("%d\n", ans[i]+1);
    printf("%d\n", f);
    return 0;
}