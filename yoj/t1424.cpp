#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,int> pli;

const int N = 5500;

int n, scnt;
ll x[N], y[N], dist[N], g[N][N];

inline bool check(ll r, ll x, ll y, ll xx, ll yy) {
    return std::abs(x-xx) <= r && std::abs(y-yy) <= r;
}

ll solve() {
    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;
    priority_queue<pli,vector<pli>,greater<pli>> pq;
    pq.push(make_pair(0,0));
    while (!pq.empty()) {
        pli cur = pq.top(); pq.pop();
        ll d = cur.first; int u = cur.second;
        if (u == n-1) return d;
        if (d > dist[u]) continue;
        for (int v = 0; v < n; v++) {
            ll w = g[u][v];
            if (w + d < dist[v]) {
                dist[v] = w + d;
                pq.push(make_pair(dist[v],v));
            }
        }
    }
    return -1;
}

int main() {
    memset(g, 0x3f, sizeof(g));
    scanf("%d%d", &n, &scnt);
    for (int i = 0; i < n; i++) scanf("%lld%lld", &x[i], &y[i]);
    ll st[2], r, t;
    while (scnt--) {
        scanf("%lld%lld%lld%lld", &st[0], &st[1], &r, &t);
        for (int i = 0; i < n; i++) {
            if (!check(r, st[0], st[1], x[i], y[i])) continue;
            for (int j = i + 1; j < n; j++) {
                if (!check(r, st[0], st[1], x[j], y[j])) continue;
                g[i][j] = min(g[i][j], t);
                g[j][i] = min(g[j][i], t);
            }
        }
    }
    ll ans = solve();
    if (~ans) printf("%lld\n", ans);
    else printf("Nan\n");
    return 0;
}