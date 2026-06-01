#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXM 100
#define MAXN 500

int M, N, INF = 0x3f3f3f3f;
int dist[MAXN];
_Bool g[MAXN][MAXN], close[MAXN];

// n <= 500, 朴素dijkstra即可
int solve() {
    memset(dist, 0x3f, sizeof(dist));
    memset(close, 0, sizeof(close));
    dist[0] = 0;
    for (int i = 0; i < N; ++i) {
        int m = -1;
        for (int j = 0; j < N; ++j) {
            if ((m == -1 || dist[j] < dist[m]) && !close[j]) 
                m = j;
        }
        if (m == -1 || dist[m] == INF) break;
        close[m] = 1;
        for (int j = 0; j < N; ++j) {
            if (!close[j] && g[m][j]) 
                dist[j] = dist[m] + 1 < dist[j] ? dist[m] + 1 : dist[j];
        }
    }
    if (dist[N - 1] == INF) return -1;
    else return dist[N - 1] - 1;
}

// IO不好写
int main() {
    memset(g, 0, sizeof(g));
    scanf("%d %d", &M, &N);

    // 这段很重要
    while (getchar() != '\n');
    int c;
    while ((c=getchar()) == '\n');
    ungetc(c, stdin);

    int cnt = 0, stop[MAXN];
    char line[1024];
    for (int i = 0; i < M; ++i) {
        cnt = 0;
        if (!fgets(line, sizeof(line), stdin)) 
            break;
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\r' || line[len - 1] == '\n')) 
            line[--len] = '\0';
        char *token = strtok(line, " ");
        while (token != NULL) {
            int num = atoi(token);
            stop[cnt++] = num - 1;
            token = strtok(NULL, " ");
        }
        for (int j = 0; j < cnt; ++j) {
            for (int k = j + 1; k < cnt; ++k) {
                g[stop[j]][stop[k]] = true;
            }
        }
    }

    int ans = solve();
    if (~ans) 
        printf("%d\n", ans);
    else 
        printf("NO\n");

    return 0;
}