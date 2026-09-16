#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int n, len[N], in[N], dp[N];
vector<int> g[N];

int solve() {
    memset(dp, -1, sizeof(dp));
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in[i] == 0) {
            dp[i] = len[i];
            q.push(i);
        }
    }
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v: g[u]) {
            dp[v] = max(dp[v], dp[u] + len[v]);
            if (--in[v] == 0) q.push(v);
        }
    }
    int ans = -1;
    for (int i = 0; i < n; i++) ans = max(ans, dp[i]);
    return ans;
}

int main() {
    char buf[550];
    int u, v;
    scanf("%d", &n);
    while (getchar() != '\n');
    for (int i = 0; i < n; i++) {
        fgets(buf, sizeof(buf), stdin);
        char* tok = strtok(buf, " ");
        u = atoi(tok) - 1; // strtoll(tok, nullptr, 10)
        tok = strtok(NULL, " ");
        len[u] = atoi(tok);
        tok = strtok(NULL, " ");
        while (tok) {
            v = atoi(tok); 
            if (!v) break;
            v--;
            g[u].push_back(v);
            tok = strtok(NULL, " ");
            in[v]++;
        }
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}