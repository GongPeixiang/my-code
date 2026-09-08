#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int N = 105, K = 30; // (1<<30)<int: ok

int n, m, c[N], l, k;
// int dp[N][1<<K]; 1<<K is too large
map<int,int> f[N], g[N];
vector<pii> adj[N], rev[N];

int solve() {
    int ll = l / 2, lr = l - ll;
    f[0][1<<c[0]] = 0;
    for (int i = 1; i <= ll; i++) {
        for (int u = 0; u < n; u++) {
            for (auto& p: f[u]) {
                int stat = p.first, d = p.second;
                if (__builtin_popcount(stat) != i) continue;
                for (const auto& edge: adj[u]) {
                    int v = edge.first, w = edge.second;
                    if ((stat>>c[v]) & 1) continue;
                    int ns = stat | (1<<c[v]);
                    f[v][ns] = max(f[v][ns], d + w);
                }
            }
        }
    }
    g[n-1][1<<c[n-1]] = 0;
    for (int i = 1; i <= lr; i++) {
        for (int u = 0; u < n; u++) {
            for (auto& p: g[u]) {
                int stat = p.first, d = p.second;
                if (__builtin_popcount(stat) != i) continue;
                for (const auto& edge: rev[u]) {
                    int v = edge.first, w = edge.second;
                    if ((stat>>c[v]) & 1) continue;
                    int ns = stat | (1<<c[v]);
                    g[v][ns] = max(g[v][ns], d + w);
                }
            }
        }
    }
    int ans = -1;
    for (int u = 0; u < n; u++) {
        if (f[u].empty() || g[u].empty()) continue;
        vector<pii> vec1, vec2;
        for (auto& p: f[u]) vec1.emplace_back(p.second, p.first);
        for (auto& p: g[u]) vec2.emplace_back(p.second, p.first);
        sort(vec1.begin(),vec1.end(),greater<pii>());
        sort(vec2.begin(),vec2.end(),greater<pii>());
        for (auto& p: vec1) {
            for (auto& q: vec2) {
                if (p.first + q.first <= ans) break;
                int s1 = p.second, s2 = q.second;
                if ((s1 & s2) == (1<<c[u])) ans = max(ans, p.first + q.first);
            }
        }
    }
    return ans;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &l, &k);
    l--;
    vector<int> u(m), v(m), d(m);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    for (int i = 0; i < m; i++) scanf("%d", &u[i]);
    for (int i = 0; i < m; i++) scanf("%d", &v[i]);
    for (int i = 0; i < m; i++) scanf("%d", &d[i]);
    for (int i = 0; i < m; i++) { 
        adj[u[i]].emplace_back(v[i], d[i]);
        rev[v[i]].emplace_back(u[i], d[i]);
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}