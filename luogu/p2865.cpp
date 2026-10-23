// 严格次短路
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

constexpr int N = 5005;

int n, m, dis[N][2];
vector<pii> g[N];

void dij() {
    memset(dis, 0x3f, sizeof(dis));
    dis[0][0] = 0;
    auto cmp = [](pii& a, pii& b) { return a.second > b.second; };
    priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
    pq.push(make_pair(0, 0));
    while (pq.size()) {
        pii cur = pq.top(); pq.pop();
        int u = cur.first, d = cur.second;
        if (d > dis[u][1]) continue;
        for (auto& vw: g[u]) {
            int v = vw.first, w = vw.second;
            int nd = d + w;
            if (nd < dis[v][0]) {
                dis[v][1] = dis[v][0];
                dis[v][0] = nd;
                pq.push(make_pair(v, nd));
            } else if (nd > dis[v][0] && nd < dis[v][1]) {
                dis[v][1] = nd;
                pq.push(make_pair(v, nd));
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g[u].push_back(make_pair(v, w));
        g[v].push_back(make_pair(u, w));
    }
    dij();
    if (dis[n-1][1] == 0x3f3f3f3f) printf("-1\n");
    else printf("%d\n", dis[n-1][1]);
    return 0;
}