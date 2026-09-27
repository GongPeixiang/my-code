#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 50005, M = 5000005, INF = 0X3F3F3F3F;

int n, m, s, t, dep[N];
struct Edge {
    int to, nxt;
    ll cap;
} edge[M];
int head[N], ecnt = 0, cur[N];
ll sum = 0;

inline void add_edge(int u, int v, ll c) {
    edge[ecnt] = (Edge){v, head[u], c};
    head[u] = ecnt++;
    edge[ecnt] = (Edge){u, head[v], 0};
    head[v] = ecnt++;
}

bool bfs() {
    memset(dep, -1, sizeof(dep));
    dep[s] = 0;
    queue<int> q;
    q.push(s);
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
    return ~dep[t];
}

ll dfs(int u, ll mf) {
    if (u == t || !mf) return mf;
    ll sum = 0;
    for (int& i = cur[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (dep[v] == dep[u] + 1 && edge[i].cap > 0) {
            ll f = dfs(v, min(mf, edge[i].cap));
            if (f > 0) {
                edge[i].cap -= f;
                edge[i^1].cap += f;
                sum += f;
                mf -= f;
                if (!mf) break;
            }
        }
    }
    if (!sum) dep[u] = -1;
    return sum;
}

ll dinic() {
    ll ans = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        ans += dfs(s, INF);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n;
    s = 0, t = N - 5;
    int a, b;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        add_edge(s, i, a);
        sum += a;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b;
        add_edge(i, t, b);
        sum += b;
    }
    cin >> m;
    int k, c1, c2, v;
    for (int i = 1; i <= m; i++) {
        cin >> k >> c1 >> c2;
        sum += c1 + c2;
        add_edge(s, n + i*2-1, c1);
        add_edge(n + i*2, t, c2);
        for (int j = 0; j < k; j++) {
            cin >> v;
            add_edge(n + i*2-1, v, INF);
            add_edge(v, n + i*2, INF);
        }
    }
    ll ans = sum - dinic();
    cout << ans << '\n';
    return 0;
}