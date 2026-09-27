#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int N = 105;

int n, g[N][N], dist[N];
bool vis[N];
struct Node { 
    int u, w; 
    bool operator<(const Node& other) const { return w > other.w; }
};

ll prim() {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    priority_queue<Node, vector<Node>> pq;
    dist[0] = 0;
    pq.push(Node{0, 0});
    ll ans = 0, cnt = 0;
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int u = cur.u, w = cur.w;
        if (vis[u]) continue;
        vis[u] = true; ++cnt;
        ans += w;
        for (int i = 0; i < n; ++i) {
            if (!vis[i] && g[u][i] < dist[i]) {
                dist[i] = g[u][i];
                pq.push(Node{i, dist[i]});
            }
        }
    }
    if (cnt == n) return ans;
    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) 
            scanf("%d", &g[i][j]);
    ll ans = prim();
    printf("%lld\n", ans);
    return 0;
}