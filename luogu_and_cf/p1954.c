#include <stdio.h>
#include <string.h>

#define N 2005
#define M 10005

int n, m, ans[N], in[N], cpyin[N], t[N];
struct Edge { int to, nxt; } e[M];
int head[N], ecnt = 0;

#define add_edge(u,v) do {\
    e[ecnt] = (struct Edge){v, head[u]};\
    head[u] = ecnt++;\
} while(0) 

#define swap(T,a,b) do { T tmp = a; a = b; b = tmp; } while(0)

int pq[N*5], pq_cnt = 0; // big heap

void pq_push(int u) 
{
    int cur = pq_cnt;
    pq[pq_cnt++] = u;
    while (t[pq[cur]] > t[pq[(cur-1)/2]]) {
        swap(int, pq[cur], pq[(cur-1)/2]);
        cur = (cur - 1) / 2;
    }
}

int pq_pop() 
{
    int ret = pq[0];
    pq[0] = pq[--pq_cnt];
    int cur = 0;
    while (1) {
        int l = cur*2+1, r = cur*2+2;
        int big = cur;
        if (l < pq_cnt && t[pq[l]] > t[pq[big]]) big = l;
        if (r < pq_cnt && t[pq[r]] > t[pq[big]]) big = r;
        if (big == cur) break;
        swap(int, pq[cur], pq[big]);
        cur = big;
    }
    return ret;
}

void topo() 
{
    int cnt = 0;
    for (int i = 1; i <= n; i++) 
        if (!in[i]) pq_push(i);
    while (pq_cnt) {
        int cur = pq_pop();
        ans[cnt++] = cur;
        for (int i = head[cur]; ~i; i = e[i].nxt) {
            int to = e[i].to;
            if (--in[to] == 0) pq_push(to);
        }
    }
    for (int i = cnt - 1; i >= 0; i--) printf("%d%c", ans[i], " \n"[i == 0]);
}

int solve(int x) 
{
    memcpy(in, cpyin, sizeof(in));
    memset(pq, 0, sizeof(pq));
    pq_cnt = 0;
    int tot = 0;
    for (int i = 1; i <= n; i++) if (!in[i]) pq_push(i);
    while (pq_cnt) {
        int cur = pq_pop();
        if (cur == x) continue;
        if (n - tot > t[cur]) break;
        tot++;
        for (int i = head[cur]; ~i; i = e[i].nxt) {
            int to = e[i].to;
            if (--in[to] == 0) pq_push(to);
        }
    }
    return n - tot;
}

int main() 
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &t[i]);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        add_edge(b, a);
        in[a]++;
    }
    memcpy(cpyin, in, sizeof(in));
    topo();
    for (int i = 1; i <= n; i++) printf("%d ", solve(i));
    putchar('\n');
    return 0;
}