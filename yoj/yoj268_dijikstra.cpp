#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max();
int n, s, d;
vector<vector<int>> graph;

// 第一个代表距离，第二个代表节点编号
struct compare {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        if (a.first != b.first) 
            return a.first > b.first; 
        return a.second > b.second;
    }
};

void dijkstra() {
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
    
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto[dist_u, u] = pq.top();
        pq.pop();
        if (dist_u > dist[u]) 
            continue;
        if (u == d) 
            break;
        for (int v = 0; v < n; v++) {
            int w = graph[u][v];
            if (w != -1 && dist[u] != INF) {
                int new_dist = w + dist[u];
                if (new_dist < dist[v]) {
                    parent[v] = u;
                    dist[v] = new_dist;
                    pq.push({dist[v], v});
                }
                else if (new_dist == dist[v] && (u < parent[v] || parent[v] == -1)) {
                    parent[v] = u;
                } 
            }
        }
    }
    if (dist[d] == INF) {
        cout << -1 << '\n';
        return;
    }

    vector<int> track;
    int trace = d;
    while (trace != -1) {
        track.push_back(trace);
        trace = parent[trace];
    }
    reverse(track.begin(), track.end());

    for (int i = 0; i < track.size() - 1; i++) 
        cout << track[i] << "->";
    cout << track[track.size() - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s >> d;
    graph.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    dijkstra();
    
    return 0;
}