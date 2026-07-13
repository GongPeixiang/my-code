#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 505
#define Q 300000

int n, dist[N], pq_cnt = 0;
bool ok[N][N];
struct Node {
    int u, g;
} pq[Q];

#define swap(T, a, b) do { T tmp = a; a = b; b = tmp; } while(0)

void pq_push(struct Node node) 
{
    int cur = pq_cnt;
    pq[pq_cnt++] = node;
    while (cur > 0 && pq[cur].g < pq[(cur-1)/2].g) {
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
        if (l < pq_cnt && pq[l].g < pq[small].g) small = l;
        if (r < pq_cnt && pq[r].g < pq[small].g) small = r;
        if (small == cur) break;
        swap(struct Node, pq[cur], pq[small]);
        cur = small;
    }
    return ret;
}

int solve() 
{
    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;
    pq_push((struct Node){0, 0});
    while (pq_cnt != 0) {
        struct Node cur = pq_pop();
        int u = cur.u, g = cur.g;
        if (g > dist[u]) continue;
        if (u == n - 1) return g - 1;
        for (int v = 0; v < n; ++v) {
            if (!ok[u][v]) continue;
            int ng = g + 1;
            if (ng < dist[v]) {
                dist[v] = ng;
                pq_push((struct Node){v, ng});
            }
        }
    }
    return -1;
}

int main() 
{
    int m, stop[N], cnt;
    char line[2*N];
    scanf("%d %d", &m, &n);
    while (getchar() != '\n');
    memset(ok, 0, sizeof(ok));
    while (m--) {
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\r\n")] = '\0';
        cnt = 0;
        char *tok = strtok(line, " ");
        while (tok) {
            stop[cnt++] = atoi(tok) - 1;
            tok = strtok(NULL, " ");
        }
        // the bus is one-way
        for (int i = 0; i < cnt; ++i) {
            for (int j = i + 1; j < cnt; ++j) {
                int u = stop[i], v = stop[j];
                ok[u][v] = true;
            }
        }
    }
    int ans = solve();
    if (~ans) printf("%d\n", ans);
    else printf("NO\n");
    return 0;
}