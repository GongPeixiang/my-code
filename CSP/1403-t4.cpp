#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define sq(_a) ((_a)*(_a))

const int N = 105, M = 105, K = 105;

int n, m, k, dis[N+M][K];
ll r, x[N+M], y[N+M];
struct Node {
    int u, d;
    int _k;
};

// s = 0, t = 1
int bfs() {
    memset(dis, 0x3f, sizeof(dis));
    dis[0][0] = 0;
    queue<Node> q;
    q.push((Node){0, 0, 0});
    while (q.size()) {
        Node cur = q.front(); q.pop();
        int u = cur.u, d = cur.d, ck = cur._k;
        int lim;
        if (u == 1) return d;
        lim = (ck==k) ? n : n+m;
        for (int v = 0; v < lim; v++) {
            if (sq(x[u]-x[v]) + sq(y[u]-y[v]) <= r) {
                int nd = d + 1, nk = ck + (v>=n);
                if (nd < dis[v][nk]) {
                    dis[v][nk] = nd;
                    q.push((Node){v, nd, nk});
                }
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d%d%d%lld", &n, &m, &k, &r);
    r = r*r;
    for (int i = 0; i < n+m; i++) scanf("%lld%lld", &x[i], &y[i]);
    int ans = bfs(); 
    if (~ans) printf("%d\n", ans - 1); // 中转数 = 路径长度-1
    return 0;
}