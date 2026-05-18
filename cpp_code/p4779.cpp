#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
int n, m, s;
vector<vector<pair<int, long long>>> adj;  // 邻接表

void dijkstra() {
    vector<long long> dist(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, 
        greater<pair<long long, int>>> pq;
    dist[s - 1] = 0;
    pq.push({0, s - 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        // 如果当前距离大于记录的距离，跳过
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    for (int i = 0; i < n; i++) cout << dist[i] << ' ';
    cout << endl;
}

int main() {
    cin >> n >> m >> s;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u - 1].push_back({v - 1, w});
    }
    
    dijkstra();
    return 0;
}