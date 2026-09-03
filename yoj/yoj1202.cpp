#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,ll> pil;

const int N = 100, M = 5050;

int n, m, mnode, mc, c[N], head[N], ecnt = 0;
struct Edge { int to, nxt, d; } edge[M];
map<pil,ll> dist;   map<pil,bool> inq;

struct Node {
    ll stat;
    int tag;
    int u;
};

inline void add_edge(int u, int v, int d) {
    edge[ecnt] = (Edge){v, head[u], d};
    head[u] = ecnt++;
}

ll solve() {
    queue<Node> q;
    dist[make_pair(0,1)] = 0;
    inq[make_pair(0,1)] = true;
    // c[0] = 0, and init_stat = 1;
    q.push((Node){1, 1, 0});
    while (!q.empty()) {
        Node cur = q.front(); q.pop();
        ll stat = cur.stat;
        int tag = cur.tag, u = cur.u;
        inq[make_pair(u,stat)] = false;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to, d = edge[i].d;
            ll nstat = stat | (1<<v); int ntag = tag | (1<<c[v]);
            if (dist[v][nstat])
        }
    }
}

int tmp[3][M];

int main() {
    memset(head, -1, sizeof(head));
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m >> mnode >> mc;
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int k = 0; k < 3; k++) 
        for (int i = 0; i < m; i++) cin >> tmp[k][i];
    for (int i = 0; i < m; i++) add_edge(tmp[0][i], tmp[1][i], tmp[2][i]);
    
}