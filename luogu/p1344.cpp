#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 35, M = 1005;
constexpr int MOD = M*2+1;

int n, m, dep[N];
struct Edge {
    int to, nxt;
    ll cap;
} edge[M*2];
int head[N], ecnt = 0, cur[N];

inline void add_edge(int u, int v, ll c) {
    edge[ecnt] = (Edge){v, head[u], c};
    head[u] = ecnt++;
    edge[ecnt] = (Edge){u, head[v], 0};
    head[v] = ecnt++;
}

bool bfs() {
    memset(dep, -1, sizeof(dep));
    dep[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (dep[v] == -1 && edge[i].cap > 0) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
    return ~dep[n-1];
}

ll dfs(int u, ll push) {
    if (u == n-1 || push == 0) return push;
    ll sum = 0;
    for (int& i = cur[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (dep[v] == dep[u] + 1 && edge[i].cap > 0) {
            ll f = dfs(v, min(push, edge[i].cap));
            if (!f) continue;
            edge[i].cap -= f;
            edge[i^1].cap += f;
            push -= f;
            sum += f;
            if (push == 0) break;
        }
    }
    if (sum == 0) dep[u] = -1;
    return sum;
}

ll dinic() {
    ll ans = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        ans += dfs(0, 4e18);
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    int x, y; ll c;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> c;
        x--; y--;
        add_edge(x, y, c * MOD + 1);
    }
    ll ans = dinic();
    cout << (ans / MOD) << ' ' << (ans % MOD) << '\n';
    return 0;
}