#include <bits/stdc++.h>
using namespace std;

constexpr int N = 6005;

int n, dp[N][2], in[N], root;
vector<int> g[N];

void dfs(int u) {
    for (int v: g[u]) {
        dfs(v);
        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &dp[i][1]);
    int u, v;
    for (int i = 0; i < n-1; i++) {
        scanf("%d%d", &v, &u);
        v--; u--;
        in[v]++;
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        if (!in[i]) { 
            root = i; 
            break;
        }
    }
    dfs(root);
    int ans = max(dp[root][0], dp[root][1]);
    printf("%d\n", ans);
    return 0;
}