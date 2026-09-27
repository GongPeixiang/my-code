#include <bits/stdc++.h>
using namespace std;

const int N = 100005, M = 100005;

int n, m, in[N], ans[N], cnt;
struct Edge { int to, nxt; } edge[M];
int head[N], ecnt = 0;

inline void add_edge(int u, int v) {
    edge[ecnt] = (Edge){v, head[u]};
    head[u] = ecnt++;
}

bool topo() {
    cnt = 0;
    priority_queue<int> pq; // stl的堆就是大顶堆
    for (int i = 1; i <= n; i++) if (in[i]==0) pq.push(i);
    while (!pq.empty()) {
        int cur = pq.top(); pq.pop();
        ans[cnt++] = cur;
        for (int i = head[cur]; ~i; i = edge[i].nxt) {
            int to = edge[i].to;
            if (--in[to] == 0) pq.push(to);
        }
    }
    reverse(ans, ans + cnt);
    return cnt == n;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ecnt = 0;
        memset(in, 0, sizeof(in));
        memset(head, -1, sizeof(head));
        scanf("%d%d", &n, &m);
        int u, v;
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &u, &v);
            add_edge(v, u); // rev-graph
            in[u]++;
        }
        bool flg = topo();
        if (flg) {
            for (int i = 0; i < cnt; i++) printf("%d ", ans[i]);
            putchar('\n');
        } else 
            printf("Impossible!\n");
    }
    return 0;
}