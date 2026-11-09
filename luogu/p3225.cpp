#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1005, M = 1005;

int n, m;
struct Edge { int to, nxt; } e[M];
int hd[N], ecnt = 0;
bool exist[N];

inline void add_edge(int u, int v) {
    e[ecnt] = (Edge){v, hd[u]};
    hd[u] = ecnt++;
}

int root, dcnt = 0;
int dfn[N], low[N], _time = 0;
bool cut[N];
vector<int> dcc[N];
stack<int> s;

void tar(int u) {
    dfn[u] = low[u] = ++_time;
    s.push(u);
    if (u == root && hd[u] == -1) {
        dcc[++dcnt].push_back(u);
        return;
    }
    int ch = 0;
    for (int i = hd[u]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) {
            ch++;
            tar(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                if (u != root) cut[u] = 1;
                dcnt++;
                int vv;
                do { vv=s.top();s.pop(); dcc[dcnt].push_back(vv); } while(vv!=v);
                dcc[dcnt].push_back(u);
            }
        } else low[u] = min(low[u], dfn[v]);
    }
    if (u == root && ch >= 2) cut[u] = 1;
}

int main() {
    int kase = 0;
    while (scanf("%d", &m)==1 && m) {
        memset(hd, -1, sizeof(hd));
        memset(exist, 0, sizeof(exist));
        memset(cut, 0, sizeof(cut));
        ecnt = 0;
        n = 0;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            exist[u] = exist[v] = 1;
            n = max(n, max(u, v));
            add_edge(u, v);
            add_edge(v, u);
        }
        for (int i = 1; i <= n; i++) dcc[i].clear();
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        dcnt = 0;
        _time = 0;
        stack<int>().swap(s);
        for (int i = 1; i <= n; i++) {
            if (exist[i] && !dfn[i]) {
                root = i;
                tar(i);
            }
        }
        ll ans = 0, ways = 1;
        for (int i = 1; i <= dcnt; i++) {
            ll sz = static_cast<ll>(dcc[i].size());
            ll cnt = 0;
            for (int u: dcc[i]) if (cut[u]) cnt++;
            if (cnt == 0) { // 等价于全图仅有这一个DCC
                ans += 2;
                ways *= sz * (sz-1) / 2;
            } else if (cnt == 1) {
                ans += 1;
                ways *= sz - 1;
            }
        }
        printf("Case %d: %lld %lld\n", ++kase, ans, ways);
    }
    return 0;
}