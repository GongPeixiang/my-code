#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 105, M = 50005;
const ll INF = 0X3f3f3f3f;

int n, m, s = 0, t = N - 1, dep[N];
struct Edge {
    int to, nxt;
    ll cap;
} edge[M];
int head[N], ecnt = 0, cur[N];

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
    if (u == t || mf == 0) return mf;
    ll sum = 0;
    for (int& i = cur[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].to;
        if (dep[v] == dep[u] + 1 && edge[i].cap > 0) {
            ll f = dfs(v, min(mf, edge[i].cap));
            edge[i].cap -= f;
            edge[i^1].cap += f;
            sum += f;
            mf -= f;
            if (mf == 0) break;
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
    // 前向星一定记得初始化head为-1!!! --- 2026.9.2 debug 1hour
    memset(head, -1, sizeof(head));
    cin >> m >> n;
    int c, p;
    ll sum = 0;
    char buf[550];
    while (cin.get() != '\n');
    for (int i = 1; i <= m; i++) {
        cin.getline(buf, sizeof(buf));
        // buf[strcspn(buf, "\r\n")] = '\0';
        char* tok = strtok(buf, " ");
        if (tok) p = stoi(tok);
        sum += p;
        add_edge(s, i, p);
        tok = strtok(NULL, " ");
        while (tok) {
            int num = stoi(tok);
            add_edge(i, m + num, INF);
            tok = strtok(NULL, " ");
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> c;
        add_edge(m + i, t, c);
    }
    ll ans = sum - dinic();
    for (int i = 1; i <= m; i++) 
        if (~dep[i]) cout << i << ' ';
    cout.put('\n');
    for (int i = m + 1; i <= m + n; i++) 
        if (~dep[i]) cout << i-m << ' ';
    cout << '\n' << ans << '\n';
    return 0;
}