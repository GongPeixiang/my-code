// 优先队列，适用于稀疏图
#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e6;
int n, m; // n顶点数, m边数
int min_cost = 0;
vector<vector<pair<int, int>>> graph;

vector<int> prim(int src) {
    vector<bool> vis(n, false);
    vector<int> low_cost(n, INF);  // low_cost[i]表示顶点i到生成树的最短距离
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, 
        greater<pair<int, int>>> pq;

    low_cost[src] = 0;
    pq.push({0, src});
    // 注意，先不要标记vis[src] = true!

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (vis[u]) 
            continue;
        vis[u] = true;
        min_cost += d;

        for (auto &[v, w] : graph[u]) {
            if (!vis[v] && w < low_cost[v]) {
                low_cost[v] = w;
                parent[v] = u;
                pq.push({w, v});
            }
        }
    }

    return parent;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    graph.resize(n);
    int u, v, w;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<int> parent = prim(0);
    
    cout << "最小生成树总权值: " << min_cost << '\n';
    cout << "最小生成树边:" << '\n';
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) 
            cout << parent[i] << " -- " << i << '\n';
    }
}