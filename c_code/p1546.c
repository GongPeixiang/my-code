#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 105
#define Q 40005
typedef long long ll;

int n, g[N][N];
struct Node {
    int u, d;
} pq[Q];
int pq_cnt = 0, dist[N];
bool vis[N];

#define swap(T, x, y) do { T tmp = x; x = y; y = tmp; } while(0)

void pq_push(struct Node node) 
{
    int cur = pq_cnt;
    pq[pq_cnt++] = node;
    while (cur > 0 && pq[cur].d < pq[(cur-1)/2].d) {
        swap(struct Node, pq[cur], pq[(cur-1)/2]);
        cur = (cur - 1) / 2;
    }
}

struct Node pq_pop() 
{
    struct Node ret = pq[0];
    pq[0] = pq[--pq_cnt];
    int cur = 0;
    while (1) {
        int l = 2 * cur + 1, r = 2 * cur + 2;
        int small = cur;
        if (l < pq_cnt && pq[l].d < pq[small].d) small = l;
        if (r < pq_cnt && pq[r].d < pq[small].d) small = r;
        if (small == cur) break;
        swap(struct Node, pq[cur], pq[small]);
        cur = small;
    }
    return ret;
}

ll solve() 
{
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    ll ans = 0, cnt = 0;
    dist[0] = 0;
    pq_push((struct Node){0, 0});
    while (pq_cnt != 0) {
        struct Node cur = pq_pop();
        int u = cur.u, d = cur.d;
        if (vis[u]) continue;
        vis[u] = true; ++cnt;
        ans += d;
        for (int i = 0; i < n; ++i) {
            if (!vis[i] && g[u][i] < dist[i]) {
                dist[i] = g[u][i];
                pq_push((struct Node){i, dist[i]});
            }
        }
    }
    if (cnt == n) return ans;
    return -1;
}

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) 
            scanf("%d", &g[i][j]);
    ll ans = solve();
    if (~ans) printf("%lld\n", ans);
    return 0;
}