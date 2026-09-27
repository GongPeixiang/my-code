#include <bits/stdc++.h>
using namespace std;

constexpr int N = 20005, K = 15;

int n, m, k, s, t, dist[N*K];
struct Edge { int v, w; };
vector<Edge> g[N*K]; // n*(k+1)
struct Node {
    int u, d;
    bool operator<(const Node& other) const { return d > other.d; }
};

#define id(x,i) (x + (i) * n) 

int dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[id(s,0)] = 0;
    priority_queue<Node, vector<Node>> pq;
    pq.push((Node){id(s,0), 0});
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
    for (int i = 0; i <= k; i++) ans = min(ans, dist[id(t,i)]);
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k >> s >> t;
    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        for (int j = 0; j <= k; j++) {
            g[id(a,j)].push_back((Edge){id(b,j), c});
            g[id(b,j)].push_back((Edge){id(a,j), c});
            if (j < k) {
                g[id(a,j)].push_back((Edge){id(b,j+1), 0});
                g[id(b,j)].push_back((Edge){id(a,j+1), 0});
            }
        }
    }
    cout << dijkstra() << '\n';
    return 0;
}