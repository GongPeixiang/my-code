#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long ll;

const int N = 100005;

int n, m, dis[N];
bool vis[N];
vector<pii> g[N];
struct Node {
    int u, d;
    bool operator<(const Node& other) const { return d > other.d; }
};

ll prim() {
    ll ans = 0;
    int cnt = 0;
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    priority_queue<Node, vector<Node>> pq;
    pq.push((Node){1, 0});
    while (pq.size()) {
        Node cur = pq.top(); pq.pop();
        int u = cur.u, d = cur.d;
        if (vis[u]) continue;
        vis[u] = 1;
        ans += d;
        cnt++;
        for (auto& vw: g[u]) {
            int v = vw.first, w = vw.second;
            if (!vis[v] && w < dis[v]) {
                dis[v] = w;
                pq.push((Node){v, w});
            }
        }
    } 
    if (cnt != n) return -1;
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }
    printf("%lld\n", prim());
    return 0;
}