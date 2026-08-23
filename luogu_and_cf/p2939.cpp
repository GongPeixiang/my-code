#include <bits/stdc++.h>
using namespace std;

constexpr int N = 10005, K = 25;

int n, m, k, dist[N*K];
struct Edge { int v, w; };
vector<Edge> g[N*K]; // n*(k+1), layered-graph
struct Node { 
    int u, d;
    bool operator<(const Node& other) const { return d > other.d; }
};

#define id(x,i) (x + (i) * n) 

int dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[id(0,0)] = 0;
    priority_queue<Node, vector<Node>> pq;
    pq.push((Node){id(0,0),0});
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int u = cur.u, d = cur.d;
        if (d > dist[u]) continue;
        for (Edge e : g[u]) {
            int v = e.v, w = e.w;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push((Node){v, dist[v]});
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i <= k; i++) ans = min(ans, dist[id(n-1,i)]);
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    int x, y, t;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> t;
        x--; y--;
        for (int j = 0; j <= k; j++) {
            g[id(x,j)].push_back((Edge){id(y,j), t});
            g[id(y,j)].push_back((Edge){id(x,j), t});
            if (j < k) {
                g[id(x,j)].push_back((Edge){id(y,j+1), 0});
                g[id(y,j)].push_back((Edge){id(x,j+1), 0});
            } 
        }
    }
    int ans = dijkstra();
    cout << ans << '\n';
    return 0;
}