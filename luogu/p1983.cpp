#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005, M = 1005;

int n, m, dp[N+M], in[N+M];
bool s[N];
vector<int> adj[N+M];

int solve() {
    queue<int> q;
    for (int i = 0; i < n + m; i++) { 
        if (!in[i]) {
            q.push(i);
            dp[i] = 1;
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v: adj[u]) {
            if (v < n) dp[v] = max(dp[v], dp[u] + 1);
            else dp[v] = max(dp[v], dp[u]); // virtual node
            if (--in[v] == 0) q.push(v);
        }
    }
    int ans = -1;
    for (int i = 0; i < n + m; i++) ans = max(ans, dp[i]);
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    int k, stop;
    for (int t = 0; t < m; t++) {
        memset(s, 0, sizeof(s));
        scanf("%d", &k);
        int src = N, dst = -1;
        while (k--) {
            scanf("%d", &stop);
            s[--stop] = 1;
            src = min(src, stop);
            dst = max(dst, stop);
        }
        int vt = t + n; // virtual node
        for (int i = src; i <= dst; i++) {
            if (s[i]) {
                adj[i].push_back(vt);
                in[vt]++;
            } else {
                adj[vt].push_back(i);
                in[i]++;
            }
        }
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}