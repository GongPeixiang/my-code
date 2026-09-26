#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

constexpr int N = 10005;

vector<int> g[N];
int n, up[N][31], dep[N];

void precalc() {
    stack<pii> st;
    st.push(make_pair(0,0)); // {root,root};
    dep[0] = 0;
    while (!st.empty()) {
        auto tmp = st.top(); st.pop();
        int u = tmp.first, p = tmp.second;
        up[u][0] = p;
        for (int k = 1; k < 31; k++) up[u][k] = up[up[u][k-1]][k-1];
        for (int v: g[u]) {
            if (v != p) {
                dep[v] = dep[u] + 1;
                st.push(make_pair(v,u));
            }
        }
    }
}

void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 31; k++) up[u][k] = up[up[u][k-1]][k-1];
    for (int v: g[u]) {
        if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = 30; k >= 0; k--) 
        if (dep[u]-(1<<k) >= dep[v]) u = up[u][k];
    if (u == v) return u;
    for (int k = 30; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int main() {
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // precalc();
    dfs(0,0);
}