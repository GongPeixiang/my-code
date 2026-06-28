#include <bits/stdc++.h>
using namespace std;
const int INF = 1e8;

struct Edge {
    int src;
    int dst;
    int w;
};

vector<long long> dist;
vector<Edge> edges;

bool bellman_ford(int source, int V) {
    dist[source] = 0;
    for (int i = 1; i <= V - 1; i++) {
        bool update = false;
        for (const auto &edge : edges) {
            int u = edge.src, v = edge.dst;
            int w = edge.w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                update = true;
            }
        }
        if (!update) 
            break;
    }
    for (const auto &edge : edges) {
        int u = edge.src, v = edge.dst;
        int w = edge.w;
        if (dist[u] != INF && dist[u] + w < dist[v]) 
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    int n, m;
    while (T--) {
        dist.clear();
        edges.clear();
        cin >> n >> m;
        dist.resize(n + 1, INF);
        int u, v, w;
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
            if (w >= 0) 
                edges.push_back({v, u, w}); 
        }
        if (bellman_ford(1, n)) 
            cout << "NO" << '\n';
        else 
            cout << "YES" << '\n';
    }
}