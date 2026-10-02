#include <stdio.h>
#include <string.h>

#define N 105

int n, dep[N], up[N][8];
struct Edge { int to, nxt; } e[N*N];
int head[N], ecnt = 0;

int vis[N], q[N], qh, qt; // qh for queue_head, t for tail

#define add_edge(u,v) do {\
    e[ecnt] = (struct Edge){v, head[u]};\
    head[u] = ecnt++;\
} while(0)

#define swap(T,x,y) do{T tmp=x; x=y; y=tmp;} while(0)
#define max(x,y) ((x)>(y)?(x):(y))

void dfs(int u, int p) {
    up[u][0] = p;
    for (int k = 1; k < 8; k++) up[u][k] = up[up[u][k-1]][k-1];
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(int, u, v);
    for (int k = 7; k >= 0; k--) 
        if (dep[u]-(1<<k) >= dep[v]) u = up[u][k];
    if (u == v) return u;
    for (int k = 7; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int calc_wid() {
    qh = qt = 0;
    q[qt++] = 0;
    vis[0] = 1;
    int maxw = -1;
    while (qh != qt) {
        int wid = qt - qh;
        maxw = max(maxw, wid);
        while (wid--) {
            int u = q[qh++];
            for (int i = head[u]; ~i; i = e[i].nxt) {
                int v = e[i].to;
                if (!vis[v]) {
                    vis[v] = 1;
                    q[qt++] = v;
                }
            }
        }
    }
    return maxw;
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    int u, v;
    for (int i = 0; i < n-1; i++) {
        scanf("%d%d", &u, &v);
        u--; v--;
        add_edge(u,v);
    }
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    dfs(0, 0);
    int maxd = -1;
    for (int i = 0; i < n; i++) maxd = max(maxd, dep[i]+1);
    int maxw = calc_wid();
    int f = lca(x, y);
    int dis = 2 * (dep[x]-dep[f]) + (dep[y]-dep[f]);
    printf("%d\n%d\n%d\n", maxd, maxw, dis);
    return 0;
}