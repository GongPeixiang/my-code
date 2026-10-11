/*
 * 求最大可行解用最短路，最小可行解用最长路
 * 但是，SPFA不太稳定，这个题实测会TLE
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100005;

int n, m, cnt[N];
vector<pair<int,ll>> g[N];
ll dis[N];
bool inq[N];

bool spfa() {
    memset(dis, 0xcf, sizeof(dis));
    queue<int> q;
    dis[0] = 0;
    q.push(0); inq[0] = 1;
    while (q.size()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        int v; ll w;
        for (auto& pr: g[u]) {
            tie(v, w) = pr;
            if (dis[u] + w > dis[v]) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n+1) return false;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    int X, u, v;
    for (int i = 1; i <= n; i++) g[0].push_back(make_pair(i, 1)); // at least 1 candy
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &X, &u, &v);
        if (X == 1) {
            g[u].push_back(make_pair(v, 0));
            g[v].push_back(make_pair(u, 0));
        } else if (X == 2) g[u].push_back(make_pair(v, 1));
        else if (X == 3) g[v].push_back(make_pair(u, 0));
        else if (X == 4) g[v].push_back(make_pair(u, 1));
        else if (X == 5) g[u].push_back(make_pair(v, 0));
    }
    if (!spfa()) {
        printf("-1\n");
        return 0;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) ans += dis[i];
    printf("%lld\n", ans);
    return 0;
}