#include <bits/stdc++.h>
using namespace std;

constexpr int N = 40005;

int n, m;
map<string,int> dict;
vector<int> g[N];

namespace tar {
int dfn[N], low[N], timer = 0, scc[N], scnt = 0;
stack<int> stk;
bool vis[N];

void dfs(int u) {
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    vis[u] = 1;
    for (int v: g[u]) {
        if (!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int v;
        scnt++;
        do {
            v = stk.top(); stk.pop();
            scc[v] = scnt;
            vis[v] = 0;
        } while (v != u);
    }
}
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n;
    string G, B;
    for (int i = 0; i < n; i++) {
        cin >> G >> B;
        dict[G] = i, dict[B] = i+n;
        g[i].push_back(i+n);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> G >> B;
        g[dict[B]].push_back(dict[G]);
    }
    for (int i = 0; i < 2*n; i++) if (!tar::dfn[i]) tar::dfs(i);
    for (int i = 0; i < n; i++) {
        if (tar::scc[i] == tar::scc[i+n]) cout << "Unsafe\n";
        else cout << "Safe\n";
    }
}