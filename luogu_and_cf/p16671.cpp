#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int T = 10;
const int M = 100005, N = 30; // alphabet:26 in total
const ll INF = 0X3f3f3f3f3f3f3f3f;

char t[N];
int m, tg[N], u[M], v[M], w[M], msk[M];
ll dist[N][N][1<<T];
struct Edge { int v, w, mask; };
vector<Edge> adj[N];

struct Node {
    ll d;
    int v, st;
    bool operator<(const Node& other) const { return d > other.d; }
};

void dij(int src) {
    dist[src][src][0] = 0;
    priority_queue<Node, vector<Node>> pq;
    pq.push((Node){0, src, 0});
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        ll d = cur.d, u = cur.v, st = cur.st;
        if (d > dist[src][u][st]) continue;
        for (Edge& e: adj[u]) {
            int v = e.v, w = e.w, msk = e.mask;
            ll nd = d + w;  int nst = st | msk;
            if (nd < dist[src][v][nst]) {
                dist[src][v][nst] = nd;
                pq.push((Node){nd, v, nst});
            }
        }
    }
}

void solve() {
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 0; i < 26; i++) dij(i);
    int full = (1<<strlen(t)) - 1;
    for (int i = 0; i < m; i++) {
        ll ans = INF;
        for (int st = 0; st <= full; st++) {
            if ((st|msk[i]) == full) ans = min(ans, w[i] + dist[v[i]][u[i]][st]);
        }
        printf("%d\n", ans != INF ? ans : -1);
    }
}

int main() {
    char buf[N];
    scanf("%d%s",&m, t);
    memset(tg, -1, sizeof(tg));
    for (int i = 0; i < strlen(t); i++) tg[t[i]-'a'] = i;
    for (int i = 0; i < m; i++) {
        scanf("%s", buf);
        int len = strlen(buf);
        u[i] = buf[0] - 'a', v[i] = buf[len-1] - 'a';
        w[i] = len - 1;
        for (int j = 0; j < len; j++) 
            if (~tg[buf[j]-'a']) msk[i] |= (1<<tg[buf[j]-'a']);
        adj[u[i]].push_back((Edge){v[i], w[i], msk[i]});
    }
    solve();
    return 0;
}