#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1005, MAXM = 10005;

struct Edge {
    int u, v, w;
} edges[MAXM];
int n, m, k, fa[MAXN];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); } 

void merge(int x, int y) { fa[find(x)] = find(y); }

bool cmp(const Edge& a, const Edge& b) { return a.w < b.w; }

int kruskal() {
    int ans = 0, cnt = n;
    for (int i = 0; i < m; ++i) {
        int u = edges[i].u , v = edges[i].v, w = edges[i].w;
        if (find(u) == find(v)) continue;
        merge(u, v);
        ans += w;
        if (--cnt == k) return ans;
    }
    return -1;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    if (n == k) {
        putchar('0');
        return 0;
    }
    for (int i = 0; i < m; ++i) scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    sort(edges, edges + m, cmp);
    for (int i = 0; i < n; ++i) fa[i] = i;
    int ans = kruskal();
    if (~ans) printf("%d\n", ans);
    else printf("No Answer\n");
    return 0;
}