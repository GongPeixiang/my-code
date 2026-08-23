#include <bits/stdc++.h>
using namespace std;

constexpr int N = 100005;

int n, m, dist[N*3];
bool inq[N*3];
struct Edge { int v, w; };
vector<Edge> g[N*3];

#define t(x,i) (x + i * n)

inline void add_edge(int x, int y) {
    g[t(x,0)].push_back((Edge){t(y,0), 0});
    g[t(x,1)].push_back((Edge){t(y,1), 0});
    g[t(x,2)].push_back((Edge){t(y,2), 0});
}

void spfa() {
    memset(dist, 0xcf, sizeof(dist));
    queue<int> q;
    q.push(t(0,0));
    dist[t(0,0)] = 0;
    inq[t(0,0)] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (Edge e: g[u]) {
            int v = e.v, w = e.w;
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    int x, y, z, val;
    for (int i = 0; i < n; i++) { 
        cin >> val;
        g[t(i,0)].push_back((Edge){t(i,1), -val});
        g[t(i,1)].push_back((Edge){t(i,2), val});
    }
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> z;
        x--; y--;
        add_edge(x, y);
        if (z == 2) add_edge(y, x);
    }
    spfa();
    cout << dist[t(n-1,2)] << '\n';
    return 0;
}