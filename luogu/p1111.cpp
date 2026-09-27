#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005, M = 100005;

int n, m, fa[N];
struct Edge {
    int u, v, t;
    bool operator<(const Edge& other) const { return t < other.t; }
} edge[M];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int x, int y) { fa[find(x)] = find(y); }

int kruskal() {
    int cnt = n;
    for (int i = 0; i < n; i++) fa[i] = i;
    for (int i = 0; i < m; i++) {
        int u = edge[i].u, v = edge[i].v, t = edge[i].t;
        if (find(u) == find(v)) continue;
        merge(u, v);
        if (--cnt == 1) return t;
    }
    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> edge[i].u >> edge[i].v >> edge[i].t;
    sort(edge, edge + m);
    int ans = kruskal();
    cout << ans << '\n';
    return 0;
}