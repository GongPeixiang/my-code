#include <stdio.h>
#include <string.h>

#define MAXN 100

int n, mat[MAXN][MAXN];

struct Edge {
    int v, nxt;
} edge[MAXN * MAXN + 5];
int head[MAXN], cnt = -1;

int flg[MAXN];

int main() 
{
    memset(head, 0xff, sizeof(head));
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
            if (j >= i && mat[i][j]) {
                edge[++cnt].v = j;
                edge[cnt].nxt = head[i];
                head[i] = cnt;
            }
        }
    }
    int tmp[MAXN], tp = 0;
    memset(flg, 0, sizeof(flg));
    for (int i = 0; i < n; ++i) {
        memset(tmp, 0, sizeof(tmp));
        tp = 0;
        for (int u = head[i]; u != -1; u = edge[u].nxt) 
            tmp[tp++] = edge[u].v + 1;
        cnt = 0;
        for (int i = tp - 1; i >= 0; --i) {
            int a = tmp[i] - 1;
            if (!flg[a]) {
                printf("%d ", tmp[i]);
                flg[a] = 1;
                ++cnt;
            }
        }
        if (cnt) printf("\n");
    }
    return 0;
}