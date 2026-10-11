#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n, m, g[N][N], cpy[N][N];

int main() {
    memset(g, 0x3f, sizeof(g));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) g[i][i] = 0;
    int u, v, w;
    while (m--) {
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g[u][v] = min(g[u][v], w);
        g[v][u] = min(g[v][u], w);
    }
    for (int k = 0; k < n; k++) 
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
    int ans = INT_MAX;
    memcpy(cpy, g, sizeof(g));
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            g[i][j] = g[j][i] = 0;
            for (int x = 0; x < n; x++) 
                for (int y = 0; y < n; y++) 
                    g[x][y] = min(g[x][y], g[x][i]+g[i][y]);
            for (int x = 0; x < n; x++) 
                for (int y = 0; y < n; y++) 
                    g[x][y] = min(g[x][y], g[x][j]+g[j][y]);
            int sum = 0;
            for (int x = 0; x < n; x++) 
                for (int y = x+1; y < n; y++) 
                    sum += g[x][y];
            ans = min(ans, sum);
            memcpy(g, cpy, sizeof(g));
        }
    }
    printf("%d\n", ans);
    return 0;
}