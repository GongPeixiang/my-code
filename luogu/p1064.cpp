#include <bits/stdc++.h>
using namespace std;

int N, m;
vector<int> v, p;
vector<vector<int>> children, dp;

void dfs(int u) {
    for (int j = v[u]; j <= N; ++j) {
        dp[u][j] = v[u] * p[u];
    }
    for (int child : children[u]) {
        dfs(child);
        for (int j = N; j >= v[u]; --j) {
            for (int k = 0; k <= j - v[u]; ++k) {
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[child][k]);
            }
        }
    }
}

int main() {
    cin >> N >> m;
    v.resize(m + 1);
    p.resize(m + 1);
    children.resize(m + 1);
    dp.assign(m + 1, vector<int>(N + 1, 0));
    // 构建依赖树
    int q;
    for (int i = 1; i <= m; ++i) {
        cin >> v[i] >> p[i] >> q;
        if (q == 0) 
            children[0].push_back(i);
        else 
            children[q].push_back(i);
    }
    
    for (int root : children[0]) {
        dfs(root);
        for (int j = N; j >= 0; --j) {
            for (int k = 0; k <= j; ++k) {
                dp[0][j] = max(dp[0][j], dp[0][j - k] + dp[root][k]);
            }
        }
    }
    
    cout << dp[0][N] << '\n';
}