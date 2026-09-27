#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205;

int n, m, t[N], g[N][N];

void update(int k) {
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            g[i][j] = g[j][i] = min(g[i][j], g[i][k] + g[k][j]);
    return;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(g, 0x3f, sizeof(g));
    cin >> n >> m;
    // t0<=t1<=...<=tn(guanranteed by the input)
    for (int i = 0; i < n; i++) cin >> t[i]; 
    int u, v, w, Q, x, y, t0;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g[u][v] = g[v][u] = w;
    }
    cin >> Q;
    int k = 0;
    while (Q--) {
        cin >> x >> y >> t0;
        while (t[k] <= t0 && k < n) {
            update(k);
            k++;
        }
        if (t0 < t[x] || t0 < t[y] || g[x][y] == 0x3f3f3f3f) cout << "-1\n";
        else cout << g[x][y] << '\n';
    }
    return 0;
}