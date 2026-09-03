#include <bits/stdc++.h>
using namespace std;

constexpr int N = 505;

int n, dist[N];
bool ok[N][N];
struct Node { 
    int u, g;
    bool operator<(const Node& other) const { return g > other.g; }
};

int solve() {
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<Node> pq;
    dist[0] = 0;
    pq.push((Node){0, 0});
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int u = cur.u, g = cur.g;
        if (g > dist[u]) continue;
        if (u == n - 1) return g - 1;
        for (int v = 0; v < n; ++v) {
            if (ok[u][v]) {
                int ng = g + 1;
                if (ng < dist[v]) {
                    dist[v] = ng;
                    pq.push((Node){v, ng});
                }
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int m, stop[N], cnt = 0;
    string line;
    cin >> m >> n;
    while (cin.get() != '\n') ;
    // cin.ignore(1000, '\n');
    while (m--) {
        getline(cin, line);
        cnt = 0;
        char* tok = strtok(&line[0], " ");
        while (tok) {
            stop[cnt++] = atoi(tok) - 1;
            tok = strtok(nullptr, " ");
        }
        /* 也可以用stringstream,但是性能较差
        stringstream ss(line);
        int num = 0;
        while (ss >> num) stop[cnt++] = num - 1; 
        */
        for (int i = 0; i < cnt; ++i) {
            for (int j = i + 1; j < cnt; ++j) {
                int u = stop[i], v = stop[j];
                ok[u][v] = true;
            }
        }
    }
    int ans = solve();
    if (~ans) cout << ans << '\n';
    else cout << "NO\n";
    return 0;
}