#include <bits/stdc++.h>
using namespace std;

const int N = 20005, M = 60005;

int n, m, dis[N], cnt[N];
bool inq[N];
struct Edge {
    int to, nxt, w;
} e[M];
int head[N], ecnt;

inline void add_edge(int u, int v, int w) {
    e[ecnt] = (Edge){v, head[u], w};
    head[u] = ecnt++;
}

bool spfa() {
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    dis[0] = 0;
    q.push(0); inq[0] = 1;
    while (q.size()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return false;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        memset(head, -1, sizeof(head));
        ecnt = 0;
        int u, v, w;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            u--; v--;
            add_edge(u, v, w);
            if (w >= 0) add_edge(v, u, w);
        }
        bool flg = spfa();
        if (flg) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}