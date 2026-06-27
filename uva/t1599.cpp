#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100005, MAXM = 400005;

int n, m, dist[MAXN], cnt = -1, head[MAXN], nxt[MAXM];
struct Edge {
    int u, v, c;
} edge[MAXM];
bool vis[MAXN];

inline void add_edge(int u, int v, int c) {
    edge[++cnt] = Edge{u, v, c};
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void rev_bfs() {
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(n);
    dist[n] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = nxt[i]) {
            int v = edge[i].v;
            if (dist[v] == 0x3f3f3f3f) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

void solve() {
    memset(vis, 0, sizeof(vis));
    vis[1] = true;
    vector<int> curlyr, nxtlyr;
    vector<int> ans;
    curlyr.push_back(1);
    for (int step = 0; step < dist[1]; ++step) {
        int minc = 0x3f3f3f3f;
        nxtlyr.clear();
        for (int u: curlyr) {
            for (int i = head[u]; ~i; i = nxt[i]) {
                int v = edge[i].v, c = edge[i].c;
                if (dist[v] == dist[u] - 1) minc = min(minc, c);
            }
        }
        for (int u: curlyr) {
            for (int i = head[u]; ~i; i = nxt[i]) {
                int v = edge[i].v, c = edge[i].c;
                if (dist[v] == dist[u] - 1 && c == minc && !vis[v]) {
                    vis[v] = true;
                    nxtlyr.push_back(v);
                }
            }
        }
        ans.push_back(minc);
        curlyr = move(nxtlyr);
    }
    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    while (cin >> n >> m) {
        cnt = -1;
        memset(head, 0xff, sizeof(head));
        memset(nxt, 0xff, sizeof(nxt));
        int a, b, c;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> c;
            add_edge(a, b, c);
            add_edge(b, a, c);
        }
        rev_bfs();
        solve();
    }
    return 0;
}
