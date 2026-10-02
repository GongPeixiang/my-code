#include <bits/stdc++.h>
using namespace std;

constexpr int N = 305, M = 305;

int n, m, dp[N][M], s[N];
vector<int> g[N];

void dfs(int u) {
    dp[u][1] = s[u];
    for (int v: g[u]) dfs(v);
    for (int v: g[u]) {
        for (int j = m; j > 0; j--) 
            for (int k = 0; k < j; k++) 
                dp[u][j] = max(dp[u][j], dp[u][j-k]+dp[v][k]);   
    }
}

int main() {
    scanf("%d%d", &n, &m);
    m++; // 根节点0必选
    int k;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &k, &s[i]);
        g[k].push_back(i);
    }
    dfs(0);
    printf("%d\n", dp[0][m]);
    return 0;
}