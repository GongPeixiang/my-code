#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205, M = 6005;

int n, m, fa[N];
struct Edge {
    int u, v, w, t;
    bool operator<(const Edge& other) const { return w < other.w; }
} edge[M];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int x, int y) { fa[find(x)] = find(y); }

int kruskal(int week) {
    int cnt = n, ans = 0;
    for (int i = 0; i < n; i++) fa[i] = i;
    for (int i = 0; i < m; i++) {
        if (edge[i].t > week) continue;
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        if (find(u) == find(v)) continue;
        merge(u, v);
        ans += w;
        if (--cnt == 1) return ans;
    }
    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        edge[i].u--; edge[i].v--;
        edge[i].t = i;
    }
    sort(edge, edge + m);
    for (int i = 0; i < m; i++) cout << kruskal(i) << '\n';
    return 0;
}