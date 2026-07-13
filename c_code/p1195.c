#include <stdio.h>
#include <stdlib.h>

#define M 10005
#define N 1005

int m, n, k, pa[N];
struct Edge {
    int u, v, w;
} edges[M];

int find(int x) { return x == pa[x] ? pa[x] : find(pa[x]); }

void merge(int x, int y) { pa[find(y)] = find(x); }

int cmp(const void *a, const void *b) 
{ return ((struct Edge *)a)->w - ((struct Edge *)b)->w; }

int kruskal() 
{
    int ans = 0, cnt = n;
    for (int i = 0; i < m; ++i) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (find(u) == find(v)) continue;
        merge(u, v);
        ans += w;
        if (--cnt == k) return ans;
    }
    return -1;
}

int main() 
{
    scanf("%d %d %d", &n, &m, &k);
    if (n == k) { putchar('0'); return 0; }
    for (int i = 0; i < m; ++i) 
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    qsort(edges, m, sizeof(struct Edge), cmp);
    for (int i = 0; i < n; ++i) pa[i] = i;
    int ans = kruskal();
    if (~ans) printf("%d\n", ans);
    else printf("No Answer\n");
    return 0;
}