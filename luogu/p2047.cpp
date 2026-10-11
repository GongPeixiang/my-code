#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 105;

int n, m;
ll g[N][N], tot[N][N];

int main() {
    memset(g, 0x3f, sizeof(g));
    scanf("%d%d", &n, &m);
    int u, v; ll w;
    while (m--) {
        scanf("%d%d%lld", &u, &v, &w);
        u--; v--;
        g[u][v] = g[v][u] = min(g[u][v], w);
        tot[u][v] = tot[v][u] = 1;
    }
    for (int k = 0; k < n; k++) 
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) {
                if (g[i][k]+g[k][j] < g[i][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                    tot[i][j] = tot[i][k] * tot[k][j];
                } else if (g[i][k]+g[k][j] == g[i][j]) {
                    tot[i][j] += tot[i][k] * tot[k][j];
                }
            }
    for (int k = 0; k < n; k++) {
        double res = 0;
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                if (i!= j && k!=i && k!=j && g[i][k]+g[k][j]==g[i][j]) 
                    res += (double)(tot[i][k]*tot[k][j]) / (double)tot[i][j];
        printf("%.3f\n", res);
    }
    return 0;
}