#include <bits/stdc++.h>
using namespace std;

const int N = 1000005, M = 3000005;
const int MOD = 100003;

int n, m, dis[N], cnt[N];
vector<int> g[N];

void solve() {
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    cnt[1] = 1;
    queue<int> q;
    q.push(1);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int v: g[u]) {
            int d = dis[u] + 1;
            if (d == dis[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            } else if (d < dis[v]) {
                dis[v] = d;
                cnt[v] = cnt[u];
                q.push(v);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    solve();
    for (int i = 1; i <= n; i++) printf("%d\n", cnt[i]);
    return 0;
}