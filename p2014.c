#include <stdio.h>
#include <string.h>

#define MAXN 305
#define MAXM 305

int N, M, s[MAXN], dp[MAXN][MAXM], sz[MAXN];

struct Edge {
    int v, nxt;
} e[MAXN];
int head[MAXN], cnt = -1;

void add_edge(int u, int v) 
{
    e[++cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

static inline int max(int x, int y) { return x > y ? x : y; }

static inline int min(int x, int y) { return x < y ? x : y; }

// 必须选自己才能选子树
void dfs(int u) 
{
    sz[u] = 1;
    dp[u][1] = s[u];
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        dfs(v);
        for (int j = min(M + 1, sz[u] + sz[v]); j > 0; --j) {
            for (int k = max(0, j - sz[u]); k <= min(sz[v], j - 1); ++k) {
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k]);
            }
        }
        sz[u] += sz[v];
    } 
}

int main() 
{
    scanf(" %d %d", &N, &M);
    memset(head, 0xff, sizeof(head));
    int f;
    for (int i = 1; i <= N; ++i) {
        scanf(" %d %d", &f, &s[i]);
        add_edge(f, i);
    }
    dfs(0);
    printf("%d\n", dp[0][M+1]);
    return 0;
}